#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#define STR_SIZE 80

char * hexa_to_bin(char hexa[1000]);
char* substring(char *destination, char *source, int beg, int n);
int convert(long long n);
int power(int base, int expo);
void printarray(int arr[], int m);
long long deci_to_bin_convert(int n);
void shiftright (char myarray[], int size, int shiftBy);
void shiftright_non (char myarray[], int size, int shiftBy);


int main(int argc, char *argv[])
{

    char filetext[100]; 

    FILE *fp; 
    //fp=fopen(argv[6],"r");
    //fseek(fp,0,SEEK_SET);

    if(strcasecmp(argv[1],"gshare")==0)
{

    fp=fopen(argv[4],"r");
   
    
    int i;
    int m=atoi(argv[2]);
    int n=atoi(argv[3]);
    //int m=atoi(argv[2]);
    int prec_arr[power(2,m)];

    char actual_val; 
    char predicted_val; 

    float mispredict=0; 
    float total=0; 

   // if (strcasecmp(argv[1],"bimodal")==0)
   //{     
      // Creating an array of pow(2,m)

    
    for (i=0;i<power(2,m);i++)
    {
        //printf("%d ",i);    
        prec_arr[i]=4;
    }


        char *ghr=""; // creating global history register    
            char ghr_asol[100];

            strcpy(ghr_asol,ghr);


            for(int i=0;i<n;i++)
            {
                strcat(ghr_asol,"0");
            }



            //printf("%s",ghr_asol);

            int line=0; 




    while (fgets(filetext, 100, fp))
    {    
        
            
            //printf("Line NO: %d\n", line);

            //fgets (filetext, 100, fp);
            //printf("%s",filetext);
            //*s=hexa_to_bin(filetext);
            char* s=hexa_to_bin(filetext);
    //        printf("%s \t",s);
            

            actual_val=filetext[7];
            //total++;
            //printf("%c",actual_val);

            //printf("%s\n", ghr_asol);    


            static char new_str[200];
            strcpy(new_str, s);
            static char new_new_str[200]="";
            substring(new_new_str,new_str,24-2-m,m);    
            
            //printf("Substring is %s\n",new_new_str);
            
            
            static char last_bits[100]="";
            substring(last_bits,new_new_str,strlen(new_new_str)-n,n); // last m bits 
            //printf("Last bits %s\n", last_bits);

            //printf("previous ghr %s \n",ghr_asol);

            long long deci; 
            sscanf(last_bits, "%lld", &deci); 
            int converted_last_bits=convert(deci);
            
            //printf("Converted decimal %d \n", converted_last_bits);

            long long amar; 
            sscanf(ghr_asol, "%lld", &amar); 
            int converted_ghr_asol=convert(amar);

            //printf("Converted GHR asol %d\n", converted_ghr_asol);

            int after_xor=converted_last_bits^converted_ghr_asol; 

            //printf("after xor %d \n",after_xor);

            long int after_deci_to_bin=deci_to_bin_convert(after_xor);

           

            //printf("After XOR from deci to bin %ld \n", after_deci_to_bin);

            static char updated_xor[100]; 
            sprintf(updated_xor, "%ld", after_deci_to_bin);
            //printf("Updated XOR %s\n", updated_xor);

            //printf("%ld\n",strlen(updated_xor));

            char hi[100]="";

            
            //printf("%ld\n", strlen(ghr_asol));
            //printf("%ld\n", strlen(updated_xor));

            long len=strlen(updated_xor);
            //printf("%d",len);

            if(len<strlen(ghr_asol))
            {
                char temp_arr[100];
                for(int c=0; c<strlen(ghr_asol)-strlen(updated_xor); c++)
                {   
                    strcat(hi,"0");
                    //printf("%s\n", hi);
                    //strcpy(updated_xor,hi);
                    len++;
                    //strcpy(temp_arr, hi);
                }
                strcat(hi,updated_xor);
                strcpy(updated_xor,hi);
            }

            //printf("Final Updated XOR %s\n", updated_xor);


            long int tumi; 
            long int ami; 

            for (tumi=strlen(new_new_str), ami=strlen(updated_xor) ; tumi>=strlen(new_new_str)-strlen(updated_xor)+1, ami>=0; tumi--, ami--)
            {
                new_new_str[tumi]=updated_xor[ami];
            }

            //printf("Binary Index is going to be %s \n", new_new_str);

            //printf("%s",ghr_asol);



            long long mera; 
            sscanf(new_new_str, "%lld", &mera); 
            int converted_deci=convert(mera);
            //printf("PT index: %d \n", converted_deci); 
    //        printf("%d \t",convert(deci));

            //printf("%d \n",prec_arr[converted_deci]);
            //printf("%d", converted_deci);

            if (prec_arr[converted_deci]>=4)
                predicted_val='t';
            else
                predicted_val='n';

            if (actual_val!=predicted_val)
                {
                    mispredict++;
                    //printf("%d",mispredict);
                }


            //printf("%d\n", prec_arr[converted_deci]);

            //printf("%c\n", predicted_val);

            if(actual_val=='t' && prec_arr[converted_deci]<7)
                prec_arr[converted_deci]++;

            else if ( actual_val=='n' && prec_arr[converted_deci]>0)
                prec_arr[converted_deci]--;


            //printf("%d\n", prec_arr[converted_deci]);


            if(actual_val=='t')
            {
                shiftright(ghr_asol,strlen(ghr_asol), 1);    
                //printf("%s\n",ghr_asol );            
            }

            else if (actual_val=='n')
                shiftright_non(ghr_asol,strlen(ghr_asol), 1); 
                //printf("%s\n", ghr_asol);


            //printf("BHR now set to: %s\n",ghr_asol);

            total++;


            //printf("\n");
            //line++;    

           //break;



}

//Gshare 


    fclose(fp); 
    printf("COMMAND\n");
    printf("./sim gshare %d %d %s \n",m,n,argv[4]);
    printf("OUTPUT\n");
    printf("number of predictions:      %.0f\n",total);
    printf("number of mispredictions:   %.0f\n",mispredict);

    //printf("%d",mispredict/total);
    float misprec_ratio; 
    misprec_ratio=(mispredict/total);
    //printf("%f\n",misprec_ratio);
    printf("misprediction rate:         %.2f%\n",misprec_ratio*100);
    printf("FINAL GSHARE CONTENTS\n");

    //int index;

    
    /*for(int i=0; i<=power(2,m); i++)
    {
        printf("%d \t",prec_arr[i]);
    }
 /*   
*/
    printarray(prec_arr,m);

/*    for(int i=0;i<64;i++)
    {
        printf("%d ",i);
       // printf("%d \n",prec_arr[index]);
    }*/


}




if (strcasecmp(argv[1],"bimodal")==0)

{

    fp=fopen(argv[3],"r");
   
    
    int i;
    int m=atoi(argv[2]);
    int prec_arr[power(2,m)];

    char actual_val; 
    char predicted_val; 

    float mispredict=0; 
    float total=0;

    for (i=0;i<power(2,m);i++)
    {
        //printf("%d ",i);    
        prec_arr[i]=4;
    }




    while (fgets (filetext, 100, fp))
    {    
    
           //fgets (filetext, 100, fp);
    //        printf("%s \t",filetext);
            //*s=hexa_to_bin(filetext);
            char* s=hexa_to_bin(filetext);
    //        printf("%s \t",s);
            
            actual_val=filetext[7];
            //total++;
            //printf("%c",actual_val);

            static char new_str[200];
            strcpy(new_str, s);
            static char new_new_str[200]="";
            substring(new_new_str,new_str,24-2-m,m);    // need to change 
            
    //        printf("Substring is %s \t",new_new_str);
            
            long long deci; 
            sscanf(new_new_str, "%lld", &deci); 
            int converted_deci=convert(deci);
            //printf("%d \n", converted_deci); 
    //        printf("%d \t",convert(deci));

            //printf("%d \n",prec_arr[converted_deci]);
            //printf("%d", converted_deci);

            if (prec_arr[converted_deci]>=4)
                predicted_val='t';
            else
                predicted_val='n';

            if (actual_val!=predicted_val)
                {
                    mispredict++;
                    //printf("%d",mispredict);
                }


            if(actual_val=='t' && prec_arr[converted_deci]<7)
                prec_arr[converted_deci]++;

            else if ( actual_val=='n' && prec_arr[converted_deci]>0)
                prec_arr[converted_deci]--;


            total++;


            //break;
            
        
    }




    fclose(fp); 
    printf("COMMAND\n");
    printf("./sim bimodal %d %s\n",m,argv[3]);
    printf("OUTPUT\n");
    printf("number of predictions:      %.0f\n",total);
    printf("number of mispredictions:   %.0f\n",mispredict);

    //printf("%d",mispredict/total);
    double misprec_ratio; 
    misprec_ratio=(mispredict/total);
    //printf("%f\n",misprec_ratio);
    printf("misprediction rate:         %.2f%\n",misprec_ratio*100);
    printf("FINAL BIMODAL CONTENTS\n");

    //int index;

    
    /*for(int i=0; i<=power(2,m); i++)
    {
        printf("%d \t",prec_arr[i]);
    }*/
    

    printarray(prec_arr,m);


}



if (strcasecmp(argv[1],"hybrid")==0)
{

    fp=fopen(argv[6],"r");
   
    
    //int i;
    int hbd_chooser_k=atoi(argv[2]);  // chooser table 
    int hbd_ghr_m1=atoi(argv[3]);  //gshare m
    int hbd_ghr_n=atoi(argv[4]); // gshare n 
    int hbd_bimodal_m2=atoi(argv[5]); // bimodal m 

    //int m=atoi(argv[2]);
    int hbd_chooser_table[power(2,hbd_chooser_k)]; 

    for(int i=0;i<power(2,hbd_chooser_k);i++)
    {
        hbd_chooser_table[i]=1;
    }

    int gshare_prec_arr[power(2,hbd_ghr_m1)];

    int bimodal_prec_arr[power(2,hbd_bimodal_m2)];


    for (int i=0; i<power(2,hbd_ghr_m1); i++)
    {
        gshare_prec_arr[i]=4;

    }

    for (int i=0; i<power(2, hbd_bimodal_m2); i++)
    {
        bimodal_prec_arr[i]=4;
    }

    //char gshare_actual_val; 
    //char predicted_val; 

    float mispredict=0; 
    float total=0; 



    char *ghr=""; // creating global history register    
    char gshare_ghr_asol[100];

    strcpy(gshare_ghr_asol,ghr);


    for(int i=0;i<hbd_ghr_n;i++)
    {
        strcat(gshare_ghr_asol,"0");
    }

    
    char gshare_predicted_val; 
    char bimodal_predicted_val;


    while (fgets (filetext, 100, fp))
    { 


        char actual_val=filetext[7];



        // Gshare Prediction

            char* gshare_s=hexa_to_bin(filetext);
    //        printf("%s \t",s);

            //char gshare_actual_val=filetext[7];

            static char gshare_new_str[200];
            strcpy(gshare_new_str, gshare_s);
            static char gshare_new_new_str[200]="";
            substring(gshare_new_new_str,gshare_new_str,24-2-hbd_ghr_m1,hbd_ghr_m1);    
            
            //printf("Substring is %s\n",new_new_str);
            
            
            static char gshare_last_bits[100]="";
            substring(gshare_last_bits,gshare_new_new_str,strlen(gshare_new_new_str)-hbd_ghr_n,hbd_ghr_n); // last m bits 
            //printf("Last bits %s\n", last_bits);

            //printf("previous ghr %s \n",ghr_asol);

            long long gshare_deci; 
            sscanf(gshare_last_bits, "%lld", &gshare_deci); 
            int gshare_converted_last_bits=convert(gshare_deci);
            
            //printf("Converted decimal %d \n", converted_last_bits);

            long long gshare_amar; 
            sscanf(gshare_ghr_asol, "%lld", &gshare_amar); 
            int gshare_converted_ghr_asol=convert(gshare_amar);

            //printf("Converted GHR asol %d\n", converted_ghr_asol);

            int gshare_after_xor=gshare_converted_last_bits^gshare_converted_ghr_asol; 

            //printf("after xor %d \n",after_xor);

            long int gshare_after_deci_to_bin=deci_to_bin_convert(gshare_after_xor);

           

            //printf("After XOR from deci to bin %ld \n", after_deci_to_bin);

            static char gshare_updated_xor[100]; 
            sprintf(gshare_updated_xor, "%ld", gshare_after_deci_to_bin);
            //printf("Updated XOR %s\n", updated_xor);

            //printf("%ld\n",strlen(updated_xor));


            char gshare_hi[100]="";

            
            //printf("%ld\n", strlen(ghr_asol));
            //printf("%ld\n", strlen(updated_xor));

            long gshare_len=strlen(gshare_updated_xor);
            //printf("%d",len);

            if(gshare_len<strlen(gshare_ghr_asol))
            {
                char gshare_temp_arr[100];
                for(int gshare_c=0; gshare_c<strlen(gshare_ghr_asol)-strlen(gshare_updated_xor); gshare_c++)
                {   
                    strcat(gshare_hi,"0");
                    //printf("%s\n", hi);
                    //strcpy(updated_xor,hi);
                    gshare_len++;
                    //strcpy(temp_arr, hi);
                }
                strcat(gshare_hi,gshare_updated_xor);
                strcpy(gshare_updated_xor,gshare_hi);
            }

            //printf("Final Updated XOR %s\n", updated_xor);



            long int gshare_tumi; 
            long int gshare_ami; 

            for (gshare_tumi=strlen(gshare_new_new_str), gshare_ami=strlen(gshare_updated_xor) ; gshare_tumi>=strlen(gshare_new_new_str)-strlen(gshare_updated_xor)+1, gshare_ami>=0; gshare_tumi--, gshare_ami--)
            {
                gshare_new_new_str[gshare_tumi]=gshare_updated_xor[gshare_ami];
            }

            //printf("Binary Index is going to be %s \n", new_new_str);

            //printf("%s",ghr_asol);



            long long gshare_mera; 
            sscanf(gshare_new_new_str, "%lld", &gshare_mera); 
            int gshare_converted_deci=convert(gshare_mera);
            //printf("PT index: %d \n", converted_deci); 
    //        printf("%d \t",convert(deci));

            //printf("%d \n",prec_arr[converted_deci]);
            //printf("%d", converted_deci);

            if (gshare_prec_arr[gshare_converted_deci]>=4)
                gshare_predicted_val='t';
            else
                gshare_predicted_val='n';



            // Bimodal


            char* bimodal_s=hexa_to_bin(filetext);
    //        printf("%s \t",s);
            
            //char bimodal_actual_val=filetext[7];
            //total++;
            //printf("%c",actual_val);

            static char bimodal_new_str[200];
            strcpy(bimodal_new_str, bimodal_s);
            static char bimodal_new_new_str[200]="";
            substring(bimodal_new_new_str,bimodal_new_str,24-2-hbd_bimodal_m2,hbd_bimodal_m2);    // need to change 
            
    //        printf("Substring is %s \t",new_new_str);
            
            long long bimodal_deci; 
            sscanf(bimodal_new_new_str, "%lld", &bimodal_deci); 
            int bimodal_converted_deci=convert(bimodal_deci);
            //printf("%d \n", converted_deci); 
    //        printf("%d \t",convert(deci));

            //printf("%d \n",prec_arr[converted_deci]);
            //printf("%d", converted_deci);

            if (bimodal_prec_arr[bimodal_converted_deci]>=4)
                bimodal_predicted_val='t';
            else
                bimodal_predicted_val='n';





            // chooser table index find 


            char* chooser_s=hexa_to_bin(filetext);
    //        printf("%s \t",s);
            
            //char chooser_actual_val=filetext[7];
            //total++;
            //printf("%c",actual_val);

            static char chooser_new_str[200];
            strcpy(chooser_new_str, chooser_s);
            static char chooser_new_new_str[200]="";
            substring(chooser_new_new_str,chooser_new_str,24-2-hbd_chooser_k,hbd_chooser_k);    // need to change 
            
    //        printf("Substring is %s \t",new_new_str);
            
            long long chooser_deci; 
            sscanf(chooser_new_new_str, "%lld", &chooser_deci); 
            int chooser_converted_deci=convert(chooser_deci);


            if (hbd_chooser_table[chooser_converted_deci]>=2)
            {
                if(actual_val=='t' && gshare_prec_arr[gshare_converted_deci]<7)
                gshare_prec_arr[gshare_converted_deci]++;

                else if ( actual_val=='n' && gshare_prec_arr[gshare_converted_deci]>0)
                gshare_prec_arr[gshare_converted_deci]--;

                if (actual_val!=gshare_predicted_val)
                {
                    mispredict++;
                }

            }

            else
            {
                if(actual_val=='t' && bimodal_prec_arr[bimodal_converted_deci]<7)
                bimodal_prec_arr[bimodal_converted_deci]++;

                else if ( actual_val=='n' && bimodal_prec_arr[bimodal_converted_deci]>0)
                bimodal_prec_arr[bimodal_converted_deci]--;

                if (actual_val!=bimodal_predicted_val)
                {
                    mispredict++;
                }
            }


            if(actual_val=='t')
            {
                shiftright(gshare_ghr_asol,strlen(gshare_ghr_asol), 1);    
                //printf("%s\n",ghr_asol );            
            }

            else if (actual_val=='n')
                shiftright_non(gshare_ghr_asol,strlen(gshare_ghr_asol), 1); 
                //printf("%s\n", ghr_asol);


            if(actual_val==gshare_predicted_val && actual_val!=bimodal_predicted_val && hbd_chooser_table[chooser_converted_deci]<3)
            {
                hbd_chooser_table[chooser_converted_deci]++;
            }

            else if(actual_val==bimodal_predicted_val && actual_val!=gshare_predicted_val && hbd_chooser_table[chooser_converted_deci]>0)
            {
                hbd_chooser_table[chooser_converted_deci]--;
            }




            total++;

    }


    fclose(fp);



    /*fp=fopen(argv[6],"r");
   
    
    //int i;
    int hbd_chooser_k=atoi(argv[2]);  // chooser table 
    int hbd_ghr_m1=atoi(argv[3]);  //gshare m
    int hbd_ghr_n=atoi(argv[4]); // gshare n 
    int hbd_bimodal_m2=atoi(argv[5]); // bimodal m 
*/




    printf("COMMAND\n");
    printf("./sim hybrid %d %d %d %d %s\n",hbd_chooser_k,hbd_ghr_m1,hbd_ghr_n,hbd_bimodal_m2,argv[6]);
    printf("OUTPUT\n");
    printf("number of predictions:      %.0f\n",total);
    printf("number of mispredictions:   %.0f\n",mispredict);

    //printf("%d",mispredict/total);
    float misprec_ratio; 
    misprec_ratio=(mispredict/total);
    //printf("%f\n",misprec_ratio);
    printf("misprediction rate:         %.2f%\n",misprec_ratio*100);
    printf("FINAL CHOOSER CONTENTS\n");

    printarray(hbd_chooser_table,hbd_chooser_k);
    printf("FINAL GSHARE CONTENTS\n");

    printarray(gshare_prec_arr,hbd_ghr_m1); 

    printf("FINAL BIMODAL CONTENTS\n");

    printarray(bimodal_prec_arr,hbd_bimodal_m2);


}


    return 0;
}

void shiftright (char myarray[], int size, int shiftBy)
{
    if(shiftBy > size){
        shiftBy = shiftBy - size;
    }
    if(size == 1){
        //do nothing
    }
    else{
        char temp;
        //for loop to print the array with indexes moved up (to the right) --> by 2
        for (int i=0; i < size; i++)
        {
            temp = myarray[size-shiftBy];
            myarray[size-shiftBy] = myarray[i];
            myarray[i] = temp;
        }
        myarray[0]='1';

    }
}



void shiftright_non (char myarray[], int size, int shiftBy)
{
    if(shiftBy > size){
        shiftBy = shiftBy - size;
    }
    if(size == 1){
        //do nothing
    }
    else{
        char temp;
        //for loop to print the array with indexes moved up (to the right) --> by 2
        for (int i=0; i < size; i++)
        {
            temp = myarray[size-shiftBy];
            myarray[size-shiftBy] = myarray[i];
            myarray[i] = temp;
        }
        myarray[0]='0';

    }
}




long long deci_to_bin_convert(int n) 
{
    long long bin = 0;
    int rem, i = 1, step = 1;
    while (n != 0) {
        rem = n % 2;
        //printf("Step %d: %d/2, Remainder = %d, Quotient = %d\n", step++, n, rem, n / 2);
        n /= 2;
        bin += rem * i;
        i *= 10;
    }
    return bin;
}





void printarray(int prec_arr[], int m)
{   

    int i=0;
    //printf("%d\t", i);
    //printf("%d\n",prec_arr[i]);
    while( i<power(2,m))
    {
        printf("%d \t",i);
        printf("%d \n",prec_arr[i]);
        i++;
    }


/*
    for (int i=0;i<power(2,m);i++)
    {
        printf("%d \t",i);
        printf("%d \n",prec_arr[i]);
    }*/
}

int convert(long long n) {
    int dec = 0, i = 0, rem;
    while (n != 0) {
        rem = n % 10;
        n /= 10;
        dec += rem * power(2, i);
        ++i;
    }
    return dec;
}

int power(int base, int exponent)
{
int result=1;
for (exponent; exponent>0; exponent--)
{
result = result * base;
}
return result;
}


char* substring(char *destination, char *source, int beg, int n)
{
    // extracts n characters from source string starting from beg index
    // and copy them into the destination string
    while (n > 0)
    {
        *destination = *(source + beg);

        destination++;
        source++;
        n--;
    }

    // null terminate destination string
    *destination = '\0';

    // return the destination string
    return destination;
}


char *  hexa_to_bin(char hexa[1000])
{
    
    //hexa[1000]; 
    long int i=0;   
    //hexa="302d28"; 
    //scanf("%s",hexa);
    //printf("%s\n", hexa);
    //strncpy( full_str, "", strSize );
    char *mam="";
    static char full_str[200];
    strcpy(full_str, mam);
        while (hexa[i])

    {

        switch (hexa[i])

        {

        case '0':

            strcat(full_str,"0000"); break;

        case '1':

            strcat(full_str,"0001"); break;

        case '2':

            strcat(full_str,"0010"); break;

        case '3':

            strcat(full_str,"0011"); break;

        case '4':

            strcat(full_str,"0100"); break;

        case '5':

            strcat(full_str,"0101"); break;

        case '6':

            strcat(full_str,"0110"); break;

        case '7':

            strcat(full_str,"0111"); break;

        case '8':

            strcat(full_str,"1000"); break;

        case '9':

            strcat(full_str,"1001"); break;

        case 'A':

            strcat(full_str,"1010"); break;

        case 'B':

            strcat(full_str,"1011"); break;

        case 'C':

            strcat(full_str,"1100"); break;

        case 'D':

            strcat(full_str,"1101"); break;

        case 'E':

            strcat(full_str,"1110"); break;

        case 'F':

            strcat(full_str,"1111"); break;

        case 'a':

            strcat(full_str,"1010"); break;

        case 'b':

            strcat(full_str,"1011"); break;

        case 'c':

            strcat(full_str,"1100"); break;

        case 'd':

            strcat(full_str,"1101"); break;

        case 'e':

            strcat(full_str,"1110"); break;

        case 'f':

            strcat(full_str,"1111"); break;

        }

        i++;

    }
    char *t=full_str;
    //printf("%s",full_str);
    return t;
}



