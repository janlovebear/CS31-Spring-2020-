//
//  orders.cpp
//  Project 3
//
//  Created by Jingnu An on 5/4/20.
//  Copyright © 2020 Jingnu An. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
#include <cctype>
#include <cmath>
using namespace std;

bool isValidUppercaseStateCode(string stateCode);
int countCases(string orders, char status, int& caseCount);
bool hasValidSyntax(string orders);

int main() {
    assert(hasValidSyntax("CA18+"));
    assert(!hasValidSyntax("CA123"));
    int cases;
    cases = -999;    // so we can detect whether countCases sets cases
    assert(countCases("ca+", '+', cases) == 1 && cases == -999);
    assert(countCases("", '+', cases) == 0  &&  cases == 0);
    cases = -999;    // so we can detect whether countCases leaves cases unchanged
    assert(countCases("", '#', cases) == 3  &&  cases == -999);
    assert(countCases("cA0+Ny00+WV000-", '+', cases) == 2  &&  cases == -999);
    cerr << "All tests succeeded" << endl;
}

bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
    "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.GU.HI.ID.IL.IN.IA.KS."
        "KY.LA.ME.MD.MA.MI.MN.MS.MO.MP.MT.NE.NV.NH.NJ.NM.NY.NC."
        "ND.OH.OK.OR.PA.PR.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
        stateCode.find('.') == string::npos  &&  // no '.' in stateCode
        codes.find(stateCode) != string::npos);  // match found
}


bool hasValidSyntax(string orders){
    if(orders == "") {return true;}
    int i=0;
    string stateCode = "";
    while(i < orders.size())
    {
        // look for alphabetic characters
        for(i=i; i<orders.size(); i++)
        {
            //once we found a letter, we change it to its upper case and throw it into an empty string
            if(isalpha(orders.at(i)))
                {stateCode += toupper(orders.at(i));}
            //stop the current for loop once we hit a non-alphabetic character
            else break;
        }
        //to come to this point, we either hit a non-alphabetic character, or we've reached the last character of the input string
        //check if we've collected a valid state code
        if(!isValidUppercaseStateCode(stateCode)) {return false;}
        //reset the backet and get ready for the next loop
        stateCode = "";
        //at this point we've had a valid state code
        //check we have at least one digit right after a statecode
        if(!isdigit(orders.at(i))){return false;}
        //now we look for more digits, if there are no more digits we get out of the loop
        for(i=i;i<orders.size();)
        {
            if(isdigit(orders.at(i))) {i++;}
            else break;
        }
        //for cases like CA123, FL123456, i at this point would be 5 which is out of range, so we back up by 1
        if(i==orders.size()){i--;}
        
        if(orders.at(i) =='+' || orders.at(i) =='-') {i++;}
        else return false;
    }
    return true;
}

int countCases(string orders, char status, int& caseCount)
{
    int tempCaseCount = 0;
    int whereIam = 0;
    int i = 0;
    
  if(!hasValidSyntax(orders)) {return 1;}
  else if (hasValidSyntax(orders))
  {
    if(status != '+' && status != '-') {return 3;}
    //for an empty string, we stop it here, set caseCount to 0, and return 0
    else if (orders == "")
        {
            caseCount = 0;
            return 0;
        }
    else
    {
        //this for loop goes over the entire orders string, and looks for 0 cases
        for(whereIam = unsigned(orders.size()-1); whereIam!=0; whereIam--)
        {
            //look for + or -, from the right to the left of the string
            if(!isdigit(orders.at(whereIam)) && !isalpha(orders.at(whereIam)))
            {
                //we change string like "123" to a number 123
                for(whereIam = whereIam-1; isdigit(orders.at(whereIam)); whereIam--)
                {
                    //methods here is that distance between two consecutive intergers is always 1
                    //and 123 = 3*10^0 + 2*10^1 + 1*10^2
                    tempCaseCount += pow(10, i) * (orders.at(whereIam) - '0');
                    i++;
                }
                i=0;
                //I let the counter whereIam to go back to the right by 1, so we would start the next loop from the first nondigit char
                whereIam++;
                //at the end of every digit calculation loop, we detect if we've had a zero case count
                if(tempCaseCount == 0) {return 2;}
                //reset the tempcaseCout and get ready for the next state order
                tempCaseCount = 0;
            }
        }
        //reset tempCaseCount, just to be sure
        tempCaseCount = 0;
        //this for loop looks for the correct status and calculate cases in that status
        for(whereIam = unsigned(orders.size()-1); whereIam!=0; whereIam--)
        {
            if(orders.at(whereIam) == status)
            {
                for(whereIam = whereIam-1; isdigit(orders.at(whereIam)); whereIam--)
                {
                    tempCaseCount += pow(10, i) * (orders.at(whereIam) - '0');
                    i++;
                }
                i=0;
                whereIam++;
            }
        }
        //once we are done, asign the value in tempCaseCount to caseCount
        caseCount = tempCaseCount;
    }
    }
    return 0;
}

