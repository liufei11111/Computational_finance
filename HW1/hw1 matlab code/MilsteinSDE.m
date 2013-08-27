function Output = MilsteinSDE(S_0,K,vol,r,T,d,iter,steps,type)
%% Milstein numerical solution for spot, with Monte Carlo simulation

dt = T/steps; % delta t
S0 = S_0*ones(1,iter); % starting price
S = zeros(steps,iter);
S(1,:) = S0;
muT = (r - d - 0.5*vol^2)*dt;
sigmaT = vol*sqrt(dt);

for k = 1:steps-1
    a = randn(1,iter);
    S(k+1,:) = S(k,:) + muT*S(k,:) + sigmaT*S(k,:).*a + ...
        0.5*(vol^2)*S(k,:).*(dt*a.^2 - dt);
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
