//
//  main.cpp
//  SchedulingAlgorithms
//
//  Created by Utkarsh Khandelwal on 29/03/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

using integer = unsigned long long int;


int static ReadingInterface(const string &fileName, unsigned long &jobsCount, vector<vector<int>> &jobsWeightLength)
{
    ifstream input(fileName, ios::in);
    int iLine = 0;
    string lineData;
    while (getline(input, lineData))
    {
        if(iLine == 0)
        {
            jobsCount = std::stoul(lineData);
            iLine++;
        }
        else
        {
            stringstream lineStream(lineData);
            
            vector<int> jobData;  //First One in this vector is weight, whereas second one will be length
            int valueRead;
            while(lineStream >> valueRead)
            {
                jobData.emplace_back(valueRead);
            }
            iLine++;
            jobsWeightLength.emplace_back(jobData);
        }
    }
    return iLine;
}

bool static ScheduleJobs(const int method, vector<vector<int>> jobs, integer &weightedTotalTime)
{
    if(method == 1)  //Onn the basis of differences
    {
        auto Comparator = [](const vector<int> &first, const vector<int> &second)->bool{
            auto diff_First = first[0] - first[1];
            auto diff_Second = second[0] - second[1];
            if( diff_First > diff_Second)
                return true;
            else if(diff_First < diff_Second)
                return false;
            else
            {
                auto weight_First = first[0];
                auto weight_Second = second[0];
                if(weight_First > weight_Second)
                    return true;
                else
                    return false;
            }
        };
        std::sort(jobs.begin(), jobs.end(), Comparator);
    }
    else if(method == 2)
    {
        auto Comparator = [](const vector<int> &first, const vector<int> &second)->bool{
            
            double weigthFirst = first[0];
            double lengthFirst = first[1];
            double ratio_First = weigthFirst/lengthFirst;
            
            double weightSecond = second[0];
            double lengthSecond = second[1];
            double ratio_Second = weightSecond/lengthSecond;
            
            
            if( ratio_First > ratio_Second)
                return true;
            else
                return false;
        };
        std::sort(jobs.begin(), jobs.end(), Comparator);
    }
    else
        return false;

    vector<integer> jobCompletionTimes;
    integer timeElapsed = 0;
    for(auto job : jobs)
    {
        timeElapsed = timeElapsed + job[1];
        jobCompletionTimes.emplace_back(timeElapsed);
    }
    long long weightedCompletionTime = 0;
    for(int iJob = 0; iJob < jobs.size(); ++iJob)
    {
        integer currJobWeight = jobs[iJob][0];
        integer currTimeElapsed = jobCompletionTimes[iJob];
        integer currWeightedTime = currJobWeight * currTimeElapsed;
        weightedCompletionTime += currWeightedTime;
    }
    weightedTotalTime = weightedCompletionTime;
    return true;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    string inputPath;
    if(argc == 2)
    {
        inputPath = argv[1];
    }
    else
        return 1;

    unsigned long totalJobsCount = 0;
    vector<vector<int>> jobsWeightLength;
    int linesRead = ReadingInterface(inputPath, totalJobsCount, jobsWeightLength);
    integer weightedTotalTime1;
    bool jobsScheduled1 = ScheduleJobs(1, jobsWeightLength, weightedTotalTime1);
    integer weightedTotalTime2;
    bool jobsScheduled2 = ScheduleJobs(2, jobsWeightLength, weightedTotalTime2);
    if(jobsScheduled1== false || jobsScheduled2== false)
        return 1;
    
    cout << "Weighted Completion Time By Diff is:   " << weightedTotalTime1 << endl;
    cout << "Weighted Completion Time By Ratio is:   " << weightedTotalTime2 << endl;
    return 0;
}
