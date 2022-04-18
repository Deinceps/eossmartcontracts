#pragma once

#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>

#include <string>

namespace eosiosystem {
   class system_contract;
}

namespace eosio {

   using std::string;

   class [[eosio::contract("fee")]] fee : public contract {
      public:
         using contract::contract;

		 [[eosio::action]] void fee(const name& a, const asset& v);
         
		 using fee_action = eosio::action_wrapper<"fee"_n, &fee::fee>;
		 struct accounts
     {
       eosio::asset balance;
       uint64_t primary_key() const {return balance.symbol.code().raw();}
     };
     typedef eosio::multi_index< eosio::name("accounts"), accounts > accounts_table;

   };

}
