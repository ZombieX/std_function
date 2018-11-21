
#include<iostream>
#include<functional>


auto pi() { return 3.1415; }

class e {
public:
	auto operator()()const {
		return 2.718;
	}
};

template<class R,class ...Args>
auto call_or(const std::function< R(Args...) >& f,R&&r) {
	return f ? f() : r;
}

template<class R,class ... Args>
auto check(const std::function<R(Args...)>& t) {
	std::cout <<"callable, !callable = " << static_cast<bool>(t)<<", "<< !t << "\n";
	std::cout <<"target_type().name = " << t.target_type().name() << "\n"; 
	using f_type = R(*)(Args...);
	std::cout << "(target == null) = " << (t.target<f_type>() == nullptr) << "\n";
	std::cout<<"call_or(f, -0.) = "<<call_or(t, -0.)<<"\n";
	std::cout << "\n";
}



int main() {

	std::cout << std::boolalpha;

	std::function<double()> fx;
	//fx();		//DEAD

//	initial check
//	std::cout <<"call_or in initial = "<< call_or(fx, 0.12345) << "\n\n";
	check(fx);
	
//	change function
	fx = e{};
	check(fx);

//	change function
	fx = pi;
	check(fx);
	

// target test
	std::cout << "\n---target---\n";
	auto* np = fx.target<void()>();
	std::cout << "np is null = " << (np == nullptr) << "\n";

	auto* fp = fx.target<double()>();
	std::cout <<"fp is null == "<< (fp==nullptr) << "\n";
	//	std::cout << (*fp)() << "\n";	//	DEAD


	auto* fp2 = fx.target<double(*)()>();
	std::cout << "fp2 is null == " << (fp2 == nullptr) << "\n";
	std::cout << (*fp2)() << "\n";		// alive


	return 0;
}