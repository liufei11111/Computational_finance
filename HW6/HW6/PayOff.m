function payoff=PayOff(option,spot)

payoff=max(spot-option.Strike,0);