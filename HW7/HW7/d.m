function d=d(s, T,opt, choose)
	 log_s=log(s);
	if (choose==true)
		 d=(1/(opt.Vol*sqrt(T)))*(log_s+(opt.InterestRate+0.5*opt.Vol*opt.Vol)*T);
	else d= (1/(opt.Vol*sqrt(T)))*(log_s+(opt.InterestRate-0.5*opt.Vol*opt.Vol)*T);
    end