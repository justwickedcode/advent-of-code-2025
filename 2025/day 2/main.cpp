#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <set>

long long repeatNumber(long long s, int s_len, int k)
{
    long long repeated = 0;
    long long multiplier = 1;
    for (int i = 0; i < k; i = i + 1)
    {
        repeated = repeated * static_cast<long long>(std::pow(10, s_len)) + s;
    }
    return repeated;
}

// Part 1
long long sumInvalidIDs_Part1(long long start, long long end)
{
    long long sum = 0;
    int maxLen = std::to_string(end).size();

    for (int len = 2; len <= maxLen; len = len + 2)
    {
        int halfLen = len / 2;
        long long first = static_cast<long long>(std::pow(10, halfLen - 1));
        long long last = static_cast<long long>(std::pow(10, halfLen)) - 1;

        for (long long s = first; s <= last; s = s + 1)
        {
            long long val = repeatNumber(s, halfLen, 2);
            if (val >= start && val <= end)
                sum = sum + val;
        }
    }

    return sum;
}

// Part 2
long long sumInvalidIDs_Part2(long long start, long long end)
{
    std::set<long long> candidates;
    int maxLen = std::to_string(end).size();

    for (int s_len = 1; s_len <= maxLen / 2; s_len = s_len + 1)
    {
        long long first = static_cast<long long>(std::pow(10, s_len - 1));
        long long last = static_cast<long long>(std::pow(10, s_len)) - 1;

        for (long long s = first; s <= last; s = s + 1)
        {
            std::string pattern = std::to_string(s);

            for (int repeats = 2;; repeats = repeats + 1)
            {
                std::string valStr;
                for (int r = 0; r < repeats; r = r + 1)
                    valStr = valStr + pattern;

                if (valStr.size() > maxLen)
                    break;

                long long val = std::stoll(valStr);
                if (val > end)
                    break;
                if (val >= start)
                    candidates.insert(val);
            }
        }
    }

    long long sum = 0;
    for (long long val : candidates)
        sum = sum + val;
    return sum;
}

int main()
{
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open())
    {
        perror("Could not open input file");
        return 1;
    }

    std::string line;
    std::getline(inputFile, line);
    inputFile.close();

    long long totalSumPart1 = 0;
    long long totalSumPart2 = 0;

    size_t pos = 0;
    while (pos < line.size())
    {
        size_t commaPos = line.find(',', pos);
        std::string range = line.substr(pos, commaPos - pos);

        size_t dashPos = range.find('-');
        if (dashPos != std::string::npos)
        {
            long long start = std::stoll(range.substr(0, dashPos));
            long long end = std::stoll(range.substr(dashPos + 1));

            totalSumPart1 = totalSumPart1 + sumInvalidIDs_Part1(start, end);
            totalSumPart2 = totalSumPart2 + sumInvalidIDs_Part2(start, end);
        }

        if (commaPos == std::string::npos)
            break;
        pos = commaPos + 1;
    }

    std::cout << "Part 1: " << totalSumPart1 << std::endl;
    std::cout << "Part 2: " << totalSumPart2 << std::endl;

    return 0;
}
