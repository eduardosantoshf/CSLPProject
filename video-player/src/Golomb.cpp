#include <iostream>
#include <stdio.h>
#include <fstream> 
#include <vector>
#include <math.h>
#include "RBitStream.cpp"
#include "WBitStream.cpp"

using namespace std;

class Golomb {
	private:
		int m;
		int flag;
		RBitStream* rbs;
		WBitStream* wbs;
		
	public: 
	
	   	Golomb(string file, int M, int Flag){

			/**
             * Golomb Constructor
             * 
             * @param file initial file name
			 * @param M value of m
             * @param Flag flag
             */
			   
	   		if(Flag == 0){
	   			rbs = new RBitStream(file);
	   		}else{
	   			wbs = new WBitStream(file);
	   		}
	   		m = M;
	   		flag = Flag;
	   	}

	   	void encode(int n){

			/**
             * Function to encode given value
             * 
             * @param n value to be encoded
             */

	   		int sign = 0;
		   	if (n <0){
		   	    sign = 1;
		   	    n=n*(-1);
		   	}
	   		int r = n % m;
		   	int q = n / m;
		   	wbs->writeBit(sign);
		   	// Unary part
		   	for(int c = 0 ; c < q; c++){
		   		wbs->writeBit(0);
		   	}
		   	wbs->writeBit(1);
	   		if ((m & (m-1)) == 0){
		   		// Binary part
		   		int pow = log2(m);
		   		unsigned char u = (unsigned char) r;
		   		for (int i = 7 -(7-pow) -1 ; i != -1 ; i--) {
					wbs->writeBit((int)((u & (1 << i)) != 0));
				}
	   		}else{
	   			// Binary part truncated
		   		int b = ceil(log2(m));
		   		unsigned char tr = (unsigned char) r;
		   		if (r < pow(2,b) - m){
		   			wbs->writeNBits(r,b-1);
		   		} else {
		   		int bigger_r = r + pow(2,b)-m;
		   		unsigned char br = (unsigned char) bigger_r;
		   			wbs->writeNBits(bigger_r,b);
		   		}
	   		}
	   	}

	   	int decode(){

			/**
             * Function to decode value
             */

	   		int sign = rbs->readBit();
	   		int bit = rbs->readBit();
		   	int quo = 0;
		   	while(bit != 1){
		   		bit = rbs->readBit();
		   		quo++;
		   	}
	   		if ((m & (m-1)) == 0){
		   		int pow = log2(m);
		   		int r = rbs->readNBits(pow);
		   		if (sign == 0){
		   			return quo*m + r;
		   		}else{
		   			return (quo*m + r)*(-1);
		   		}
		  		
	  		} else {
	  			int b = ceil(log2(m));
	  			int z = rbs->readNBits(b-1);
	  			if (z < pow(2,b)-m){
	  				if (sign == 0){
	  					return quo*m+z;
	  				}else{
	  					return (quo*m+z)*(-1);
	  				}
	  			}else{
	  				int other_bit = rbs->readBit();
	  				int fr = (z << 1) + other_bit;
	  				if (sign == 0){
	  					return quo*m+(fr-pow(2,b)+m);
	  				}else{
	  					return (quo*m+(fr-pow(2,b)+m))*(-1);
	  				}
	  			}
	  		}
	   	}
	   	
	   	void close(){

			/**
             * Function to close golomb
             */

	   		if (flag == 1){
	   			wbs->close();
	   			wbs->closeNoWrite();
	   		}
	   	}
	   	
	   	void SkipNBytes(int n){

			/**
             * Function to skip N bytes when reading the file
             */

	   		int temp = 0;
	   		for (int i = 0; i < n; i++){
	   			temp = rbs->readNBits(8);
	   		}
	   	}
};



















