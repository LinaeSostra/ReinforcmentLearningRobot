% Printing the final weight mappings of the optimal path to the end location
% at the end of each run of both Q-Learning and SARSA
function[] = plotWeights()
figure

% Importing weights from Sarsa and Q-Learning
weightDataSarsa = importdata('weights#.csv');
weightDataQLearning = importdata('weightsQLearning.csv');
runs = 5;

for i = 1:runs
% Reshapping the weights data to the grid location associated with, and
% normalizing weights
weightRunSarsa = weightDataSarsa(i, 1:100);
weightRunSarsaNorm = reshape(weightRunSarsa/norm(weightRunSarsa), [10,10]);

weightRunQLearning = weightDataQLearning(i, 1:100);
weightRunQLearningNorm = reshape(weightRunQLearning/norm(weightRunQLearning), [10, 10]);
[X,Y] = meshgrid(1:10);

% Plotting the weight as a 2D heat map for Sarsa
subplot(runs, 2, 2*(i-1)+1);
surf(X,Y, weightRunSarsaNorm)
c = colorbar
ylim([1 10])
xlim([1 10])
title("Sarsa Weights Run #"+i)
view(2)

% Plotting the weight as a 2D heat map for Q-Learning
subplot(runs, 2, 2*i);
surf(X, Y, weightRunQLearningNorm)
c = colorbar
ylim([1 10])
xlim([1 10])
title("Q-Learning Weights Run #"+i)
view(2)
end
end