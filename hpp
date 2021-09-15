#pragma once
 
#include <eosio/eosio.hpp>
#include <eosio/ignore.hpp>
#include <eosio/transaction.hpp>

using namespace std;

class[[eosio::contract("contract")]] defferedTransaction : public eosio::contract
{
    public:
      using contract::contract;

    [[eosio::action]] void mine(ignore<eosio::name> executer, ignore<transaction> trx );
	
    using exec_action = eosio::action_wrapper<"mine"_n, &defferedTransaction::mine>;
};
