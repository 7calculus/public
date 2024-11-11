#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

string add(const string& x, const string& y){
    int nx = x.size();
    int ny = y.size();
    int carry = 0;
    int maxL = max(nx, ny);
    string result = "";
    for(int i = 0; i < maxL; i++){
        int xdig = i < nx ? x[nx - i - 1] - '0' : 0;
        int ydig = i < ny ? y[ny - i - 1] - '0' : 0;
        int sum = xdig + ydig + carry;
        carry = sum / 10;
        result.push_back(sum % 10 + '0');
    }
    if(carry) result.push_back('1');
    reverse(result.begin(), result.end());
    return result;
}
string subtract(const string& x, const string& y){
    int nx = x.size();
    int ny = y.size();
    //create duplicates to respect the fact that we've taken x and y as consts. So that we can modify fx and fy instead.
    string fx = x, fy = y;
    string result = "";
    for(int i = 0; i < nx; i++){
        int xdig = fx[nx - i - 1] - '0';
        int ydig = i < ny ? fy[ny - i - 1] - '0' : 0;
        int dif = xdig - ydig;
        
        if(dif < 0){
            xdig = xdig + 10;
            fx[nx - i - 2] =  (fx[nx - i - 2] - '0' - 1) + '0';
            dif = xdig - ydig;
        }
        result.push_back(dif + '0');
    }
    reverse(result.begin(), result.end());
    //remove trailing zeros
    while(result[0] == '0'){
        if(result.size() != 1){
            result.erase(0, 1);
        } else {
            break;
        }
    }
    return result;
}
//I made this function take string by value on purpose. Cuz if you take it by reference then you can't modify it, and so I have to create duplicates anyways
string multiply(string x, string y){
    int nx = x.size(), ny = y.size();
    while(nx > ny){y = '0' + y; ny++;}
    while(ny > nx){x = '0' + x; nx++;}
    if(nx < 2){
        return to_string((x[0] - '0')*(y[0] - '0'));
    }
    int half_n = nx / 2;
    string a = x.substr(0, nx - half_n), b = x.substr(nx - half_n), c = y.substr(0, ny - half_n), d = y.substr(ny - half_n);
    /* here instead of nx - half_n, I was just using half_n, that was all the mistake.....
    I still don't know the reason why it doesn't work for just half_n*/
    string z0 = multiply(a, c);
    string z1 = multiply(b, d);
    string z2 = subtract(multiply(add(a, b), add(c, d)), add(z0, z1));
    //padding z0 and z2 to approriate number of zeros
    for(int i = 0; i < 2 * half_n; i++) z0.push_back('0');
    for(int j = 0; j < half_n; j++) z2.push_back('0');
    string final_str = add(add(z0, z1), z2);
    //removing the zeros in the beginning if there are any
    while(final_str[0] == '0'){
        if(final_str.size() != 1){
            final_str.erase(0, 1);
        } else {
            break;
        }
    }
    return final_str;
}

int main(){
    string n1 = "3141592653589793238462643383279502884197169399375105820974944592";
    string n2 = "2718281828459045235360287471352662497757247093699959574966967627";
    cout<<multiply(n1, n2);
    return 0;
}

