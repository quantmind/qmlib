


  	inline SeedGenerator::SeedGenerator() : m_rng(42UL)  {
  		initialize();
  	}

  	
  	inline void SeedGenerator::initialize()  {
  		
  		// firstSeed is chosen based on clock() and used for the first rng       
  		qm_uns_long firstSeed = (qm_uns_long)clock();
  		MersenneTwister first(firstSeed);
  		//
  		// secondSeed is as random as it could be
  		// feel free to suggest improvements
  		qm_uns_long secondSeed = first.nextInt32();
  		MersenneTwister second(secondSeed);
  		//
  		// use the second rng to initialize the final one
  		qm_uns_long skip = second.nextInt32() % 1000;
  		qm_ulvector init(4);
  		init[0] = second.nextInt32();
  		init[1] = second.nextInt32();
  		init[2] = second.nextInt32();
  		init[3] = second.nextInt32();
  		m_rng = MersenneTwister(init);
  		for(qm_uns_long i=0; i<skip ; i++) m_rng.nextInt32();
  	}

  	inline MersenneTwister::MersenneTwister(qm_uns_long seed):mt(MersenneTwister::N)  {
  		seedInitialization(seed);
  	}

  	inline void MersenneTwister::seedInitialization(qm_uns_long seed)  {
  		// initializes mt with a seed
  		qm_uns_long s = (seed != 0 ? seed : this->initialseed());
  		mt[0]   = s & 0xffffffffUL;
  		for (mti=1; mti<N; mti++)    {
  			mt[mti] = (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti);
  			// See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. 
  			// In the previous versions, MSBs of the seed affect   
  			// only MSBs of the array mt[].                        
  			// 2002/01/09 modified by Makoto Matsumoto             
  			mt[mti] &= 0xffffffffUL;
  			// for >32 bit machines
  		}
  	}

  	inline MersenneTwister::MersenneTwister(const qm_ulvector& seeds):mt(MersenneTwister::N)  {
  		seedInitialization(19650218UL);
  		qm_Size i=1, j=0, k = (N>seeds.size() ? N : seeds.size());
  		for (; k; k--)	{
  			mt[i]  = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL)) + seeds[j] + j; /* non linear */
  			mt[i] &= 0xffffffffUL; /* for WORDqm_Size > 32 machines */
  			i++; j++;
  			if (i>=N) { mt[0] = mt[N-1]; i=1; }
  			if (j>=seeds.size()) j=0;
  		}
  		for (k=N-1; k; k--)
  		{
  			mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL)) - i; /* non linear */
  			mt[i] &= 0xffffffffUL; /* for WORDqm_Size > 32 machines */
  			i++;
  			if (i>=N) { mt[0] = mt[N-1]; i=1; }
  		}
  		mt[0] = 0x80000000UL; /*MSB is 1; assuring non-zero initial array*/
  	}

  	inline qm_uns_long MersenneTwister::nextInt32() const  {
  		qm_uns_long y;
  		static qm_uns_long mag01[2]={0x0UL, MATRIX_A};
        /* mag01[x] = x * MATRIX_A  for x=0,1 */
  		if (mti >= N)    {
  			/* generate N words at one time */
  			qm_Size kk;
  			for (kk=0;kk<N-M;kk++)	{
  				y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
  				mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
  			}
  			for (;kk<N-1;kk++)
  			{
  				y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
  				mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
  			}
  			y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
  			mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];
  			mti = 0;
    	}
    	//
    	y = mt[mti++];
    	/* Tempering */
    	y ^= (y >> 11);
    	y ^= (y << 7) & 0x9d2c5680UL;
    	y ^= (y << 15) & 0xefc60000UL;
    	y ^= (y >> 18);
    	return y;
  	}
  	
  	
  	inline qm_uns_long rndgen::initialseed() const  {
  		SeedGenerator sidgen;
  		return sidgen.get();
  	}
  	
