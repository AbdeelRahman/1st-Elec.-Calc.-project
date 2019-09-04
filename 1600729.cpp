#include <string>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <array>
using namespace std ;

 class eqn
{ 
	string lhs;
	string rhs;
 public:
	void seteqn(string v[] ,float c[],int h)
	{
		string l,r;
		l="";
		for(int i=0;i<h;i++)
	     {
		 if(i==0)
		{
		 ostringstream ss;
         c[i]=-(c[i]);
		 ss << c[i];
		 r=ss.str();
		 }
		 else
		 {
		ostringstream ss;
		string S_c;
		ss << c[i];
		S_c=ss.str();
		if(c[i]>0 && i>1)
        S_c="+"+S_c ;			
        string d=S_c+v[i];
        l+=d;
	     }
	     }
lhs=l ;
rhs=r ;
	}
	string getrhs()
	{return rhs ; }
	string getlhs()
	{return lhs;}
};


void removespaces(string x ,int a , string& e ,int& pme)
  {
	  string z[1000];
  e = "" ;
  pme = 0 ;
	for(int i=0; i<a ;i++)
	{
		z[i]=x.substr(i,1);
	if(z[i] == " ")
	   z[i].erase(0,1) ;
	   e=e+z[i]  ;
	if(z[i]=="=" || z[i]=="-" || z[i]=="+")
	pme +=1 ;	
	}
	int y=e.find("=");
	if(z[0]=="-") pme-=1;
	if(z[y+1]=="-")
    pme-=1;
    } 

void divide(string z ,int a, int y , int h ,float t[] ,string v[] )
{
  string q[50] ;
  string g[200] , c[200];
  int m=0 ;
  if(z[0] == '-')
	   m += 1;
  for(int j=0 ;j<h ;j++)
	{
	 g[j] = "" ;	
	 for(int s=m ;s<a ;s++)
	  {
	if(s==y+1 && z[y+1] == '-' )
	  m+=1;
	else if(z[s] != '+' && z[s] != '-' && z[s]!='=' )
	 {
	 g[j] += z[s] ;
	 m += 1 ;
	 }
	  else{
		m+=1 ;
		break ;
	  }
	 }


	  int f=g[j].length() ;
	 
	  for(int p=0 ;p<f ;p++)
	   {
	  q[p]=g[j].substr(p,1) ;
       if(q[p] == "0" || q[p] =="1"  || q[p] =="2" || q[p] =="3" || q[p] =="4" || q[p] =="5" || q[p] =="6" || q[p] =="7" || q[p] =="8" || q[p] =="9" || q[p] ==".")
	   c[j] += q[p] ;
	   else if (p == 0 )
	    {
		c[j] = "1" ;
		g[j]="1"+g[j];
	    break ;
		 }
	   else break;                                                     
         }
	  int r = c[j].length() ;
	  t[j]=atof(c[j].c_str()) ;
	  v[j]=g[j].substr(r);
	  
	   int k = m-2-f ;
	   if(m==a)
		   k+=1;

	   if(k == -1)                     //lhs & positive
		   t[j]=t[j] ;

	  else if(k<y && z[k]=='-' )     //negative lhs
	    t[j] = -(t[j]) ;

	  else if(k >= y && (z[k]=='='||z[k]=='+'))                //positive rhs
	  t[j]=-(t[j]) ;

	  }
	  }


                 
void summation(int& n,float c[], string v[])
{
	for(int m=0 ; m<n ;m++)
	{
		for(int l=m+1 ; l<n ;l++)
		{
			if(v[m]==v[l])
		{
			c[m] += c[l];

		for(int k=l ;k<n ;k++)
		{
		v[k]=v[k+1];
		c[k]=c[k+1];
		}
		n-=1;
		 l-=1; 
		}
			else  if(v[l]!="" && c[l]==0)
			{	
				for(int k=l ;k<n ;k++)                   
		{
		v[k]=v[k+1];
		c[k]=c[k+1];
		}
	     n-=1;
		 l-=1;
         }
	}
	}
}



void alpha(int n ,float c[], string v[])
{
for(int i=0 ; i<n ; i++)
  {
for (int j=i+1 ;j<n ;j++)
   {
	if (v[j] < v[i])
	{
	string tempV = v[i] ;
	float tempC = c[i] ;
	v[i] = v[j] ;
	c[i] = c[j];
	v[j] = tempV ;
	c[j] = tempC ;
	  }
	}
  }
}









int main()
{
	string x[100]   ;
	eqn e[100];
	float c[100][200] ;
	string v[100][200] ;
	int h[100] ;
	string f ;
	int n , pme ;
	cin >> n ;
	cin.ignore() ;
	
	for(int b=0; b<n ;b++)
	{
	getline(cin ,x[b]);
	int a=x[b].length() ;
	removespaces(x[b] ,a , f, pme) ;
	x[b] = f ;
	h[b]=pme+1 ;
	a=x[b].length() ;
	int y=x[b].find("=");
	divide(x[b], a, y ,h[b] , c[b] , v[b] ) ;
	summation(h[b],c[b],v[b]) ;
	alpha(h[b],c[b],v[b]) ;
	e[b].seteqn(v[b],c[b],h[b]);
    	}

    for(int i=1;i<n;i++)
    { 
	for(int k=0;k<h[i];k++)
	{
	int m=1;
	for(int j=0;j<h[0];j++)
	{
	if ( v[0][j]==v[i][k])                
	{
     m=0 ;
	 break ;
	}
	}
	if(m==1)
	{
		v[0][h[0]]=v[i][k];
		c[0][h[0]]=0;
		h[0]+=1;
	}
	}
	}
	alpha(h[0],c[0],v[0]);

for(int i=1;i<n;i++)                 
	{
for(int j=0;j<h[0];j++)
	{
		int m=1;
		for(int k=0;k<h[i];k++)
				if(v[0][j]==v[i][k])
				{
					m=0;
				    break;
		        }
	if(m==1)
	 {
	 v[i][h[i]]=v[0][j];
	 c[i][h[i]]=0;
	 h[i]+=1;
	}
	}
alpha(h[i],c[i],v[i]);
	}
	 

    int NumOfVars=h[0]-1;

while(1)
{
	string z ;
	getline(cin ,z); ;
	if(z=="num_vars")                                        /////////////////
		cout << NumOfVars << endl;
 

	if(z=="quit")
			break;


    if(z.substr(0,8)=="equation")                           ////////////////////
	{
		string i=z.substr(9);
		int j=atof(i.c_str());
		cout << e[j-1].getlhs() << "=" << e[j-1].getrhs() << endl;
	}


	if(z.substr(0,6)=="column")                          /////////////////////
	 {
	   string y=z.substr(7);
	   for(int i=1 ;i<=NumOfVars;i++)
	   {
	    if(y==v[0][i])
		{
		for(int j=0;j<n;j++)
		cout << c[j][i] << endl;
		 break;
		}
	   }
	  }


       
	if(z.substr(0,3)=="add")                      ///////////////////
	{
		eqn E;
		int n=h[0];
		string Ve[200];
		float Ce[200];
		string a[4];
		string s = "";
		int m ;
	for(int i=0 ; i<4 ; i++)
	{
	a[i]=z.substr(i+4,1);
	if(a[i] != " ")
		s += a[i];
	else
	{  m = i+5 ;
		break ;
	}	
	}
	string r = z.substr(m);
	int S = atof(s.c_str());
	int R = atof(r.c_str());
	for(int j=0 ;j<n;j++)
	{ 
		Ve[j]=v[S-1][j];
	    Ce[j]=c[S-1][j]+c[R-1][j];
		if(j==0)
			Ce[j]=-(Ce[j]);
    }
	summation(n,Ce,Ve);
	E.seteqn(Ve,Ce,n);
	cout << E.getlhs() << "=" << E.getrhs() << endl;
	}



	if(z.substr(0,8) == "subtract")              //////////////////////////
	{
        eqn E;
		int n=h[0];
		string Ve[200];
		float Ce[200];
		string a[4];
		string s = "";
		int m ;
	for(int i=0 ; i<4 ; i++)
	{
	a[i]=z.substr(i+9,1);
	if(a[i] != " ")
		s += a[i];
	else
	{  m = i+10 ;
		break ;
	}	
	}
	string r = z.substr(m);
	int S = atof(s.c_str());
	int R = atof(r.c_str());
	for(int j=0 ;j<n;j++)
	{ 
		Ve[j]=v[S-1][j];
	    Ce[j]=c[S-1][j]-c[R-1][j];
		if(j==0)
			Ce[j]=-(Ce[j]);
    }
	summation(n,Ce,Ve);
	E.seteqn(Ve,Ce,n);
	cout << E.getlhs() << "=" << E.getrhs() << endl;
	}




	if(z.substr(0,10)=="substitute")           /////////////////////
		{
		eqn E;
		string Ve[200];
		float Ce[200];
		string V = "";
		int n=h[0];
		int m;
		string a;
		for(int i=11; i<70 ;i++)
		{ 
			a=z.substr(i,1);
			if(a != " ")
			V += a ;
			else
			{
				m=i+1;
				break;
			}
		}
		string W1="";
		for(int j=m;j<100;j++)
			{
			a=z.substr(j,1);
			if(a != " ")
				W1 += a;
			else
			{
			m=j+1 ;
			break;
			}
            }
		string W2 = z.substr(m);
		int w1 = atof(W1.c_str());
	    int w2 = atof(W2.c_str());
		for(int k=0 ; k< n ; k++)
		{
		if(v[0][k] == V)
		{
		m = k;
		break ;
		}
		}
	for(int j=0 ;j<n;j++)
	{ 
		Ve[j]=v[w1-1][j];
		Ce[j]=c[w1-1][j]-((c[w1-1][m]/c[w2-1][m])*c[w2-1][j]);
		if(j==m)
		 Ce[j]=0;
		if(j==0)
			Ce[j]=-(Ce[j]);
	}
		summation(n,Ce,Ve);
	    E.seteqn(Ve,Ce,n);
		cout << E.getlhs() << "=" << E.getrhs() << endl;
		
	}


	if(z=="solve")                  ////////////////////
	{
	if(n != NumOfVars)
	cout<< "No Solution" ;
		else
			{
			float Cs[100][200];
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<n+1;j++)
					Cs[i][j]=c[i][j];
			}
			float s=1;
	        float p;
	for(int i=0 ;i<n-1 ;i++)
	{ 
			for(int r=i+1;r<n;r++)
			{
				if(Cs[i][i+1]==0)                           
				{
				float TempC;
				int m=i+1;
				for(int j=i+1;j<n;j++)
				{
				if(Cs[j][i+1]!=0)
				{
				m=j;
				break;
				}
				}
				for(int q=0;q<n+1;q++)
				{
				  TempC=Cs[i][q];
				  Cs[i][q]=-(Cs[m][q]);
				  Cs[m][q]=TempC;
				}
				}
				else
				{
			p=-(Cs[r][i+1]/Cs[i][i+1]);
			for(int k=i+2 ;k<n+1; k++)
			{
				Cs[r][k]+=Cs[i][k]*p;
			}
				}
			}
		s *= Cs[i][i+1];
		}
	s*=Cs[n-1][n];
	if(s==0)
	{
	cout<<"No Solution" ;
	}
	else
	{
		float m;
	for(int i=1;i<n+1;i++)
	{
	for(int j=0 ;j<n;j++)
		{
			for(int k=0;k<n+1;k++)
	{
		if(k==i)
		    Cs[j][k]=c[j][0];
		
		else
			Cs[j][k]=c[j][k];	
			}
	}


	float y=1;
	  float p;
	  for(int j=0 ;j<n-1 ;j++)
	{ 
			for(int r=j+1;r<n;r++)
			{
				if(Cs[j][j+1]==0)                    
				{
				float TempC;
				int t=j+1;
				for(int k=j+1;k<n;k++)
				{
				if(Cs[k][j+1]!=0)
				{
				t=k;
				break;
				}
				}
				for(int q=0;q<n+1;q++)
				{
				  TempC=Cs[j][q];
				  Cs[j][q]=-(Cs[t][q]);
				  Cs[t][q]=TempC;
				}
				}
				else
			{
				p=-(Cs[r][j+1]/Cs[j][j+1]);
			for(int l=j+2 ;l<n+1; l++)
			{
				Cs[r][l]+=Cs[j][l]*p;
			}
				}
			}
			y*=Cs[j][j+1];
		}
	  y*=Cs[n-1][n];
	m=y/s;
	cout<<v[0][i]<<"="<< m << endl ;
	}
    }
	}
	}



	
	if(z=="D")                                          ////////////////////////
	{
		for(int i=0;i<n;i++)
		{
			for(int j=1;j<h[0];j++)
		cout << c[i][j] << "\t" ;
			cout << endl ;
		}
	}
   



	if(z=="D_value")                          ////////////////////////
	{
		if(n != NumOfVars)
	cout<< "No Solution" ;
		else
			{
			float Cs[100][200];
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<n+1;j++)
					Cs[i][j]=c[i][j];
			}
			float s=1;
	        float p;
	for(int i=0 ;i<n-1 ;i++)                                  
	{ 
			for(int r=i+1;r<n;r++)
			{
				if(Cs[i][i+1]==0)                                 
				{
				float TempC;
				int m=i+1;
				for(int j=i+1;j<n;j++)
				{
				if(Cs[j][i+1] != 0)
				{
				m=j;
				break;
				}
				}
				for(int q=0;q<n+1;q++)
				{
				  TempC=Cs[i][q];
				  Cs[i][q]=-(Cs[m][q]);
				  Cs[m][q]=TempC;
				}
				}
				else
				{
			p=-(Cs[r][i+1]/Cs[i][i+1]);
			for(int k=i+2 ;k<n+1; k++)
			{
				Cs[r][k]+=Cs[i][k]*p;
			}
				}
			}
		s *= Cs[i][i+1];
		}
	s*=Cs[n-1][n];
        cout << s <<endl ;
    }
	}
	





		else if(z.substr(0,1)=="D" && z!="D" && z!="D_value")              /////////////////////////////
   {
	string x = z.substr(2);
	for(int i=0;i<n;i++)
	{ 
		for(int j=1;j<h[0];j++)
		{
		if(v[i][j]==x)
			cout << c[i][0] << "\t";
		else
			cout << c[i][j] << "\t";
		}
		cout << endl ;
	}
	}

	}

	return 0 ;
	}

//3
//2x1+3x2+4x3=16
//1x1+2x2+1x3=8
//3x1+1x2+2x3=13
//solve