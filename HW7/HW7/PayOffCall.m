function payoffcall=PayOffCall(option,spot)

payoffcall=max(spot-option.Strike,0);