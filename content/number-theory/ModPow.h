/**
 * Author: Noam527
 * Date: 2019-04-24
 * License: CC0
 * Source: folklore
 * Description: $b^e \bmod$ mod. Files that include this file may set
 *  their own mod (e.g. NTT); keep only one definition.
 * Usage: ll x = modpow(b, e); // b^e mod mod
 * Status: tested
 */
#pragma once

#ifndef MOD_SET /// exclude-line
const ll mod = 1000000007; // faster if const
#endif /// exclude-line

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}
