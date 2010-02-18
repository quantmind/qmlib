




QM_NAMESPACE2(math)


inline qm_real normal_dist::lndensity(qm_real x)  const  {
	qm_real u = this->standard_variate(x);
	return - 0.5 * u * u - std::log(sigma() * boost::math::constants::root_two_pi<qm_real>());
}
	
inline qm_real normal_dist::cumulative(qm_real x)  const  {
	qm_real u = this->standard_variate(x) / boost::math::constants::root_two<qm_real>();
	return boost::math::erfc(-u) / 2;
}
	
inline qm_real normal_dist::icumulative(qm_real u)  const  {
	check_u(u);
	qm_real r = -boost::math::erfc_inv(2 * u);
	r *= sigma() * boost::math::constants::root_two<qm_real>();
	r += mu();
	return r;
}
	
inline qm_complex normal_dist::characteristic_exp(const qm_complex& u) const  {
	return u * (-0.5 * sigma() * sigma() * u + qm_complex(0,mu()));
}


inline qm_real lognormal_dist::standard_variate(qm_real x) const  {
	QM_REQUIRE(x>0,"Draw must be positive in lognormal distribution");
	return (std::log(x) - mu())/sigma();
}

inline qm_real lognormal_dist::lndensity(qm_real x)  const  {
	QM_REQUIRE(x>0,"Draw must be positive in lognormal distribution");
	qm_real u = this->standard_variate(x);
	return - 0.5 * u * u - std::log(sigma() * x * boost::math::constants::root_two_pi<qm_real>());
}
	
	
inline qm_real gamma_dist::density(qm_real x)  const  {
	check_x(x);
	return boost::math::gamma_p_derivative(shape(), x / scale()) / scale();
}
	
inline qm_real gamma_dist::cumulative(qm_real x)  const  {
	check_x(x);
	return boost::math::gamma_p(shape(), x / scale());
}
	
inline qm_real gamma_dist::icumulative(qm_real u)  const  {
	check_u(u);
	return boost::math::gamma_p_inv(shape(), u) * scale();
}
	
inline qm_complex gamma_dist::characteristic_exp(const qm_complex& u) const  {
	return shape() * std::log(1.0 - mult_i(u)*scale());
}

	
inline const poisson_dist::pdist& poisson_dist::buildist(qm_uns_long k) const  {
	qm_uns_long t = m_distribution.size();
	while(t <= k)  {
		qm_real d = m_distribution[t-1].first * lambda() / k;
		qm_real c = m_distribution[t-1].second += d;
		m_distribution.push_back(pdist(d,c));
		t = m_distribution.size();
	}
	return m_distribution[k];
}
	
inline const binomial_dist::pdist& binomial_dist::buildist(qm_uns_long k) const  {
	qm_uns_long t = m_distribution.size();
	while(t <= k)  {
		qm_real d = m_distribution[t-1].first * p() * (n() - k + 1) / (k * (1.0 - p()));
		qm_real c = m_distribution[t-1].second += d;
		m_distribution.push_back(pdist(d,c));
		t = m_distribution.size();
	}
	return m_distribution[k];
}

inline qm_real discrete_distribution::cumulative(qm_real x)  const  {
	qm_uns_long k = (qm_uns_long)std::floor(x);
	return buildist(k).second;
}

inline qm_real discrete_distribution::density(qm_real x)  const  {
	qm_uns_long k = (qm_uns_long)std::floor(x);
	return buildist(k).first;
}

QM_NAMESPACE_END2

