% Prints the first 5 runs of rewards of either the Q-Learning or SARSA csv 
% results to see the change in the reward and learning over time
function [] = plotData(csvFile, isSarsa, numberOfRuns, numberOfEpisodes)
% Resolving optional parameters; by default the number of runs is 50, and
% number of episodes is 500.
if nargin > 2
    numOfRuns = numberOfRuns;
else
    numOfRuns = 50;
if nargin > 3
    numOfEpisodes = numberOfEpisodes;
else
    numOfEpisodes = 500;

% Importing the Data
data = importdata(csvFile);
episodes = data(:,1);
episodeSteps = data(:, 2);
cumulativeReward = data(:, 3);

% Initializing the Variables
windowSize = 10;
runs = 5;
smoothedRewards = zeros(runs, length(cumulativeReward)/numOfRuns - windowSize);

% Smoothing the data using a moving window of 10 for the first 5 runs
for runNumber = 1:runs
    row = numOfEpisodes * (runNumber - 1);
    for i = 1:length(smoothedRewards)
        startIndex = row + i;
        endIndex = startIndex + windowSize;
        smoothedRewards(runNumber, i) = mean(cumulativeReward(startIndex:endIndex));
    end
    % Printing the average reward and steps at the end of each run
    averageReward = mean(cumulativeReward(row+1: (row + numOfEpisodes)))
    averageSteps = mean(episodeSteps(row+1: row + numOfEpisodes))
end

% Plotting the smoothed results for the first 5 runs of said data
episodeDuration = episodes(windowSize+1:numOfEpisodes);
for runNumber = 1:runs
    subplot(runs, 1, runNumber);
    plot(episodeDuration, smoothedRewards(runNumber,:))
    % Labeling changes depending if Sarsa data or Q-learning data
    if(isSarsa)
        title('Episodic Sarsa with 10 Episode Moving Window')
    else
        title('Episodic Q-Learning with 10 Episode Moving Window');
    end
    xlabel('Episodes')
    ylabel('Cumulative Reward')
    legend("Run #"+runNumber, 'Location', 'southeast')
end
end