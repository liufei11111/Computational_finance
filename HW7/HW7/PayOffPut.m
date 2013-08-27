function payoffput=PayOffPut(option,spot)

payoffput=max(option.Strike-spot,0);