#pragma once
 
#include <eosio/eosio.hpp>
#include <eosio/ignore.hpp>
#include <eosio/transaction.hpp>

using namespace eosio;

class[[eosio::contract("wax")]] wax : public eosio::contract
{
    public:
      using contract::contract;

    [[eosio::action]] 
	void mine(eosio::ignore<eosio::name> executer, eosio::ignore<eosio::transaction> trx );
	
    using mine_action = eosio::action_wrapper<"mine"_n, &wax::mine>;
};
