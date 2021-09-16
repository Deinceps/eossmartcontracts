#include "wax.hpp"

using namespace eosio;

void wax::mine(eosio::ignore<eosio::name>, eosio::ignore<eosio::transaction> ) {
   require_auth( get_self() );
   eosio::name executer;
   _ds >> executer;

   send_deferred( (uint128_t(executer.value) << 64) | (uint64_t)current_time_point().time_since_epoch().count(), executer, _ds.pos(), _ds.remaining() );
}
