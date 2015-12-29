#include <stdio.h>
#include <gmp.h>
#include <CE_point.h>
#include <CE_curve.h>

/*CRYPTO ADDITION AND MULTIPLICATION TEST WITH ELLIPTIC CURVE
 * 
 * W256-002 PARAMETERS
	p=29053129760003294168792608562165959092241443760246818115462552210766900256539
	n=29053129760003294168792608562165959092373701855951268554864148023146302117801
	a4=12636322846729793624469679563083840758264172361222670979339367868388249333864
	a6=6588636957048278792070611320053577653658303305545676743354585000517330093110
	r4=5918447115782686335899894593498842933820444826971844169986932103542748311015
	r6=20151323192827665877267767633179262974925934008873551559554843097841781132361
	gx=1883861677302825433150080146064433926057666830312116084170909957931752465780
	gy=14879198636017871211572785279217230234540791980152267393994961559017176372361
	r=1464576486094935492092853335191361477071355015759316481846786322579007553342
 * */

CE_curve* ec_curve;

void init_variable(){
	//CE_curve(const char* p, const char* n, const char* a4, const char* a6, const CE_point* g);
	ec_curve = new CE_curve(
		"8884933102832021670310856601112383279507496491807071433260928721853918699951", //p
		"8884933102832021670310856601112383279454437918059397120004264665392731659049",  //n
		"2481513316835306518496091950488867366805208929993787063131352719741796616329",  //a4
		"4387305958586347890529260320831286139799795892409507048422786783411496715073",  //a6
		new CE_point(
			"7638166354848741333090176068286311479365713946232310129943505521094105356372", //gx
			"762687367051975977761089912701686274060655281117983501949286086861823169994" //gy
		));
		
	/*ec_curve = new CE_curve(
		"17", //p
		"19",  //n
		"2",  //a4
		"2",  //a6
		new CE_point(
			"16", //gx
			"13" //gy
		));*/
}

int main(int argc, char **argv)
{
	init_variable();	
		
	//test
	CE_point* point3;
	CE_point* point4;
	//using
	
	int count=0;
	for (int i=1;i<=5000;i++){
		mpz_t ii;
		mpz_init_set_ui(ii, i);
		point4 = ec_curve->mul(ec_curve->g, &ii);
		point3 = ec_curve->mul(point4, &ec_curve->n);	
		//point3 = ec_curve->dbl(ec_curve->g);
		//point3 = ec_curve->add(ec_curve->g, ec_curve->g);
			
		char* x = new char[100];
		char* y = new char[100];
		mpz_get_str(x, 10, point3->x);
		mpz_get_str(y, 10, point3->y);
		
		printf("i=%d\n", i);
		if (!point3->inf){
			count++;
			mpz_get_str(x, 10, point4->x);
			mpz_get_str(y, 10, point4->y);
			printf("point4 at i=%d: x=%s, y=%s\n", i, x, y);
		}
	}
	printf("count=%d", count);
	return 0;
}