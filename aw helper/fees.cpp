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
	void fees::execute(const name& account, const asset& amount_in, const int64_t& min_profit, std::vector<transfer_data>& transfers)
	{
		auto transfer = std::move(transfers.front());
        transfers.erase(transfers.begin());
		
		auto tmp = accounts_table(transfer.contract, account.value);
		auto itr = tmp.find(transfer.symbol_code.raw());
		eosio::check(itr != tmp.end(), "base token not exist");
		auto balance_init = itr->balance;
				
		action(
			permission_level{account, "active"_n},
			transfer.contract,
			"transfer"_n,
			std::make_tuple(account, transfer.receiver, amount_in, transfer.memo)
		).send();
		
		for(const auto& transfer: transfers) 
		{
			action(
				permission_level{account, "active"_n},
				get_self(),
				"trns"_n,
				std::make_tuple(account, transfer)
			).send();
		}
		
		balance_init.set_amount(balance_init.amount + min_profit);
		action(
			permission_level{account, "active"_n},
			get_self(),
			"check"_n,
			std::make_tuple(account, transfer.contract, balance_init)
		).send();
	}
	void fees::trns(const name& account, transfer_data& transfer)
	{		
		auto tmp = accounts_table(transfer.contract, account.value);
		auto itr = tmp.find(transfer.symbol_code.raw());
		auto balance = itr->balance;
		
		action(
			permission_level{account, "active"_n},
			transfer.contract,
			"transfer"_n,
			std::make_tuple(account, transfer.receiver, balance, transfer.memo)
		).send();
	}
}
