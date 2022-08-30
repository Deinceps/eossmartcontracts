#include <fees.hpp>
#include <eosio/system.hpp>

namespace eosio {
  void fees::fee(const int16_t& a, const int64_t& v)
  {
    //string planet_name = "eyeke.world";
    //if(a == 1)
    //{
    //  planet_name = "kavian.world";
    //}
    //else if(a == 2)
    //{
    //  planet_name = "magor.world";
    //}
    //else if(a == 3)
    //{
    //  planet_name = "naron.world";
    //}
    //else if(a == 4)
    //{
    //  planet_name = "neri.world";
    //}
    //else if(a == 5)
    //{
    //  planet_name = "veles.world"; 
    //}
    //state3 state3_s("m.federation"_n, eosio::name(planet_name).value);
    //const auto& state = state3_s.get( "state3"_n.value );
    
    //eosio::time_point last_fill_time = state.last_fill_time;
	//	double fill_rate = state.fill_rate;
	//	eosio::asset mine_bucket = state.mine_bucket;
    //int64_t amount = mine_bucket.amount;
    //eosio::time_point current_time = current_time_point();
    
    //if(current_time > last_fill_time)
    //{
    //  amount += static_cast<int64_t>(fill_rate) / 2;
    //}
    
    //eosio::check(amount >= v, 3080003);
  }
  void fees::log(const name& a, const int64_t& v)
  {
    //accounts_table tmp(eosio::name("alien.worlds"), a.value);
    //auto itr = tmp.find(symbol("TLM", 4).code().raw());
    //eosio::check(itr != tmp.end(), 3080003);
    //auto balance = itr->balance;
    //eosio::check(balance.amount >= v, 3080003);
  }
	void fees::check(const name& account, const name& contract, const asset& quantity)
	{
		accounts_table tmp(contract, account.value);
		auto itr = tmp.find(quantity.symbol.code().raw());
		eosio::check(itr != tmp.end(), "minimum not reached");
		auto balance = itr->balance;
		eosio::check(balance.amount >= quantity.amount, "minimum not reached");
	}
	void fees::execute(const name& account, const name& amount_in_contract, const asset& amount_in, const int64_t& min_profit, const std::vector<transfer_data> transfers)
	{
		accounts_table tmp(amount_in_contract, account.value);
		auto itr = tmp.find(amount_in.symbol.code().raw());
		eosio::check(itr != tmp.end(), "minimum not reached");
		auto balance_init = itr->balance;
		asset token_in = amount_in;

		int64_t newBalance = 0;
		for (auto transfer : transfers)
		{
			accounts_table tmp(transfer.receive_token_contract, account.value);
			itr = tmp.find(transfer.symbol_code.raw());
			int64_t old_balance = 0;
			if (itr != tmp.end())
			{
				old_balance = (itr->balance).amount;
			}
			
			action(
				permission_level(account, "active"_n),
				transfer.contract,
				"transfer"_n,
				std::make_tuple(account, transfer.receiver, token_in, transfer.memo)
			).send();
			itr = tmp.find(transfer.symbol_code.raw());
			auto balance = itr->balance;
			newBalance = balance.amount;
			balance.set_amount(newBalance - old_balance);
			token_in = balance;
		}
		
		eosio::check(newBalance - min_profit >= balance_init.amount, "minimum not reached, new: " + std::to_string(newBalance) + ", old: " + std::to_string(balance_init.amount));
	}
}
