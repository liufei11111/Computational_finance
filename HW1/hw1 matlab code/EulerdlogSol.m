function Output = EulerdlogSol(S_0,K,vol,r,T,d,iter,steps,type)
%% Euler numerical solution for log spot, with Monte Carlo simulation

dt = T/steps; % delta t
S0 = S_0*ones(1,iter); % starting price
S = zeros(steps,iter);
S(1,:) = S0;
muT = (r - d - 0.5*vol^2)*dt;
sigmaT = vol*sqrt(dt);

for k = 1:steps-1
    Z = (muT + sigmaT*randn(1,iter));
    S(k+1,:) = S(k,:).*exp(Z);
end

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
