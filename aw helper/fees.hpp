#pragma once

#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>

#include <string>

namespace eosiosystem {
   class system_contract;
}

namespace eosio {

	using std::string;
   
	struct transfer_data
	{
	    name contract;
	    name receiver;
	    name receive_token_contract;
	    string memo;
		eosio::symbol_code symbol_code;
	};

   class [[eosio::contract("fees")]] fees : public contract {
      public:
	using contract::contract;
	[[eosio::action]]
	void fee(const int16_t& a, const int64_t& v);
	[[eosio::action]]
	void log(const name& a, const int64_t& v);
	[[eosio::action]]
	void check(const name& account, const name& contract, const asset& quantity);
	[[eosio::action]]
	void execute(const name& account, const asset& amount_in, const int64_t& min_profit, std::vector<transfer_data>& transfers);
	[[eosio::action]]
	void trns(const name& account, const int64_t& old_balance, const eosio::symbol_code old_balance_symbol_code, const int64_t& need_base_token, const name& amount_in_contract, std::vector<transfer_data>& transfers);
         
	using fee_action = eosio::action_wrapper<"fee"_n, &fees::fee>;
	using log_action = eosio::action_wrapper<"log"_n, &fees::log>;
	using check_action = eosio::action_wrapper<"check"_n, &fees::check>;
	using execute_action = eosio::action_wrapper<"execute"_n, &fees::execute>;
	using trns_action = eosio::action_wrapper<"trns"_n, &fees::trns>;
	struct accounts
	{
		eosio::asset balance;
		uint64_t primary_key() const {return balance.symbol.code().raw();}
	};
	typedef eosio::multi_index< eosio::name("accounts"), accounts > accounts_table;
	
	struct state3_s
	{
		eosio::time_point last_fill_time;
		double fill_rate;
		eosio::asset bucket_total;
		eosio::asset mine_bucket;
		uint64_t primary_key() const { return "state3"_n.value; }
	};
	typedef eosio::multi_index< "state3"_n, state3_s > state3;
   };
}
