#pragma once

#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>

#include <string>

namespace eosiosystem {
   class system_contract;
}

namespace eosio {

   using std::string;

   class [[eosio::contract("fees")]] fees : public contract {
      public:
	using contract::contract;
	[[eosio::action]]
	void fee(const int16_t& a, const int64_t& v);
	[[eosio::action]]
	void log(const name& a, const int64_t& v);
	[[eosio::action]]
	void fees::check(const name& account, const name& contract, const asset& quantity);
         
	using fee_action = eosio::action_wrapper<"fee"_n, &fees::fee>;
	using log_action = eosio::action_wrapper<"log"_n, &fees::log>;
	using check_action = eosio::action_wrapper<"check"_n, &fees::check>;
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
