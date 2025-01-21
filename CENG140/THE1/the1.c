#include <stdio.h>
int getchar(void);
int codon(char array[]){
    if (array[0] == 'A'){
        if(array[1] == 'A'){
            if (array[2] == 'A' || array[2] == 'G'){
                return 'f';
            }
            else {return 'l';}
        }
        else if (array[1] == 'G') {return 's';}
    
        else if (array[1] == 'T'){
            if (array[2] == 'A' || array[2] == 'G'){return 'y';}
            else return 0;}
        if (array[1] == 'C'){
            if (array[2] == 'A' || array[2] == 'G'){return 'c';}
            else if (array[2] == 'C') {return 'w';}
            else {return 0;}
    }}
    else if (array[0] == 'G'){
        if (array[1] == 'A') {return 'l';}
        else if (array[1] == 'G') {return 'p';}
        else if (array[1] == 'T'){
            if (array[2] == 'A' || array[2] == 'G'){return 'h';}
            else if (array[2] == 'C' || array[2] == 'T'){return 'q';}
            
            }
        else if (array[1] == 'C'){return 'r';}
        }
    else if (array[0] == 'T'){
        if (array[1] == 'A'){
            if (array[2] == 'C'){return 'm';}
            else return 'i';
        }
        else if (array[1] == 'G'){return 't';}
        else if (array[1] == 'T'){
            if (array[2] == 'A' || array[2] == 'G'){return 'n';}
            else return 'k';
        }
        else if (array[1] == 'C'){
            if (array[2] == 'A' || array[2] == 'G'){return 's';}
            else return 'r';
        }
    }
    else if (array[0] == 'C'){
        if (array[1] == 'A'){return 'v';}
        else if (array[1] == 'G'){return 'a';}
        else if (array[1] == 'T'){
            if (array[2] == 'A' || array[2] == 'G'){return 'd';}
            else return 'e';
        }
        else if (array[1] == 'C') {return 'g';}}
    }
int main() {
    char genome[3000],protein[2900];
    char tri[3],first_exon[1000],last_exon[1000];
    char schar,samino;
    int a=0,b=0,p=0,protstart=0,kk = -1,ii = 0,sum = 0;
    int newa=0;
    int i = 0, j = 0, k = 0, l = 0, m=0, n = 0, entered = 0, hasmidexon = 0, hasmidexon2 = 0, hasmidexon3 = 0;
    int int1s=9999,int1e=9999,int2s=9999,int2e=9999;
    

    
    do{
        schar = getchar();
        if (schar != ' ' && schar != '\n') {genome[i] = schar;i++;} 
    }
    while(genome[i-1] != '.');
    ii = i-1;
    /*ii = toplam genome uzunluğu(nokta dahil)*/
    do{
        samino = getchar();
        if (samino != ' ' && samino != '\n') {protein[k] = samino;k++;} 
    }
    while(protein[k-1] != '.');
    
    for (p = 0; p < 3;p++){
        tri[p] = genome[i-4+p];
    }
    a = codon(tri);
    if (a != 0){
        printf("NONE");
        return 0;
    }
    /*ilk exon*/
    for (b = 0; b<=(i-3);){
        for (p = 0; p < 3;p++){
            tri[p] = genome[b+p];
        }
        a = codon(tri);

        if (a == protein[l]){
           
            b += 3;
            first_exon[l] = protein[l];
            protein[l] = 0;
            l++;
            genome[j] = 0;
            genome[j+1] = 0;
            genome[j+2] = 0;
            j+=3;
            /*printf("%c",a);*/
        }
        else {
            int1s = b;
            break;
        }
        
    }
    k+=1;
    i+=3;
    /*stop ayıklama ve sonu temizleme/sıfırlama/son exon */ /*printf(" son: ");*/
    do{

        k-=1;
        i-=3;
        for (p = 0; p < 3;p++){
            tri[p] = genome[(i+p-4)];
        }
        
        newa = codon(tri);
        if (newa == 0){k++;}
        last_exon[k-1] = protein[k-1];
        if (kk == -1) {kk = k;}
        genome[i-1] = 0;
        genome[i-2] = 0;
        genome[i-3] = 0;
        protein[k-1] = 0;
        }
    while (newa == protein[k-2] || newa == 0);
    /*kk-2,protein dizisinde . yı veriyor*/
    if (last_exon[kk-3] == 0){
        printf("NONE");
        return 0;
    }

    int2e = i-2;
    j = 0;
    while (protein[j]==0)
    {
        j++; 
    }
    protstart = j;
    /*orta kısım*/
    while (protein[j] != 0)
    {
        for (p = 0; p < 3;p++){
            tri[p] = genome[(int1s+p+m)];
        }
        newa = codon(tri);
        if (newa == protein[j]){
            j++;
            entered = 1;
            hasmidexon = 1;

            if(int1e == 9999){int1e = int1s + m - 1;}
            m+=3;
        }
        else if (entered == 1){
            entered = 0;
            hasmidexon = 0;
            int1e = 9999;
            j = protstart;
            m++;
        }
        else {m++;}
        int2s = m+int1s;
        
        if (m > 3000){entered = 0;hasmidexon = 0;break;}
    }
    
    while (hasmidexon == 0){
        /*first_exon[-1] genome içinde var mı*/
        if (genome[(int1s + n)] == 0){break;}
        for (p = 0; p < 3;p++){
            tri[p] = genome[(int1s+p+n)];          
        }
        newa = codon(tri);
        
        if (first_exon[l-1] == newa){
            /*buraya girdiği anki l'miz bize int2s, son l bize int1e hakkında bilgi veriyor*/
            if (int2s >= 3000) {int2s = int1s + n + 3;}
            int1s -= 3;
            l--;
            hasmidexon2 = 1;
        }
        else if (hasmidexon2 == 0) {n += 1;}
        else {int1e = int1s+n+2;entered = 1;break;}
    }
    n=-2;
    
    while (hasmidexon2 == 0 && hasmidexon == 0){
        if (genome[(int2e + n)] == 0){break;}
        for (p = 0; p < 3;p++){
            tri[p] = genome[(int2e+p+n)];          
        }
        newa = codon(tri);
        if (last_exon[k-1] == newa){
            if (int1e >= 3000){int1e = int2e + n-1;}
            int2e += 3;
            k++;
            hasmidexon3 = 1;
            
        }
        else if (hasmidexon3 == 0) {n -= 1;}
        else {int2s = int2e + n;entered = 1;break;}
        
    }
    sum = int1s + int2s - int1e - 1 + ii - int2e - 1;

    if (kk-1 != sum/3){
        printf("NONE");
        return 0;
    }
    if (entered == 0 || (int1s == 9999 || int1e == 9999 || int2s == 9999 || int2e == 9999) || int1s <= 0 || (((int1s < int1e) < int2s) < int2e == 0)){
        printf("NONE");
    }
    else 
    {printf("%d %d %d %d",int1s,int1e,int2s,int2e);}

    return 0;
}
