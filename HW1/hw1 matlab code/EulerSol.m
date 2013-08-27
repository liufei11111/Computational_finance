function Output = EulerSol(S_0,K,vol,r,T,d,iter,steps,type)
%% Euler numerical solution, with Monte Carlo simulation
% We use the Euler numerical solution and Monte Carlo simulation to
% cocmpute the prices for European-style options.

dt = T/steps; % delta t
S0 = S_0*ones(1,iter); % starting price
S = zeros(steps,iter);
S(1,:) = S0;
muT = (r - d - 0.5*vol^2)*dt;
sigmaT = vol*sqrt(dt);

% Loop to complete the path dependent price of the underlying
for k = 1:steps-1
    Z = (muT + sigmaT*randn(1,iter));
    S(k+1,:) = S(k,:) + muT*S(k,:) + sigmaT*randn(1,iter).*S(k,:);
end

% We select the type of option we are pricing
switch type
    case 'Call'
        Payoff = exp(-r*T)*max(0,S(end,:) - K);
        Output = mean(Payoff);
    case 'Put'
        Payoff = exp(-r*T)*max(0,K - S(end,:));
        Output = mean(Payoff);
    otherwise
        warning('No type was selected. Please choose Call or Put');
end
