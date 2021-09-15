#include "wax.hpp"

using namespace eosio;

void defferedTransaction::mine(eosio::ignore<eosio::name>, eosio::ignore<eosio::transaction> ){
   eosio::name executer;
   _ds >> executer;

   require_auth( eosio::name{"deinceps1111"} );

   send_deferred( (uint128_t(executer.value) << 64) | (uint64_t)current_time_point().time_since_epoch().count(), executer, _ds.pos(), _ds.remaining() );
}
