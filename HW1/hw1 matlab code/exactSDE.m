function Output = exactSDE(S_0,K,vol,r,T,d,iter,type)
%% Exact SDE, with Monte Carlo simulation
% We use the analytical solution and MC simulation to compute the price for
% European-style options.

muT = (r - d - 0.5*vol^2)*T;
sigmaT = vol*sqrt(T);

% Determine what type of option we are pricing
switch type
    case 'Call'
        Payoff = exp(-r*T)*max(0,S_0*exp(muT + sigmaT*randn(iter,1)) - K);
        Output = mean(Payoff);
    case 'Put'
        Payoff = exp(-r*T)*max(0,K - S_0*exp(muT + sigmaT*randn(iter,1)));
        Output = mean(Payoff);
    otherwise
        warning('No type was selected. Please choose Call or Put');
end
