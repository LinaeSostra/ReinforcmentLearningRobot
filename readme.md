# Reinforcement Learning on Robots

This project was part of a self-directed elective in my final year of undergrad to learn the fundamentals of reinforcement learning. I explored implementing approximate temporal difference learning algorithms on physical custom 3D printed robots, Benny and Bunny, to move from A to B. Halfway through the project, it became clear the algorithms and hardware had to be decoupled as it was too difficult to verify if the problems lay in the hardware or the algorithms. From the simulation results, it became clear the selected algorithms would not work for a large state space, and more powerful algorithms would be needed to teach the robots Benny and Bunny path planning from A to B.

![img_8324](https://user-images.githubusercontent.com/13898053/47622879-8b95d680-dac7-11e8-97d7-3a6e79625648.JPG)

## Simulation Setup

All of the code was written from scratch in C++; this was done for 2 reasons. (1) Once the simulation results were working as intended, then it could easily be ported to the robots that use a microcontroller with limited CPU and computation. Using a standard library such as Google Brain's Tensorflow or OpenAI's Gym would have been too large for these mobile robots. (2) I attempted to code up the exercises in Rich Sutton's and Andrew Barto's ["Introduction to Reinforcement Learning"](http://incompleteideas.net/book/the-book-2nd.html) back in the Fall of 2017 with not much success, so I wanted to prove I could write the RL algorithms even when I failed to so in the past.

The task in simulation was on a 10 by 10 grid, starting at (0, 0) to move to the end location (4, 4). In the ascii art below you can see the '^' represents the position of the simulated robot, the 'X' is the goal position, 'O' is the starting location, and '.' the other possible locations of the robot. The reward function is for every step is -1, -10 if it tries to move out of the boundaries, such as moving left from (0, 0) would result in a reward of -10 and no change in position, and 50 if it reaches the goal position (4, 4). Thus the optimal strategy should take 8 steps and an overall cumulative reward of 43. The parameters for learning were epsilon = 0.1 (exploration factor), alpha = 0.2 (step size), gamma = 1.0 (discount factor) with the four actions: Up (0), Down (1), Left (2), and Right (3). It should be noted that these parameters were not fine-tuned.

![Simulation Respresentation](https://user-images.githubusercontent.com/13898053/47628477-03c5c180-daf3-11e8-92e5-c0f70f883668.png)

## Simulation Results

Due to the algorithms not being deterministic, both the approximate episodic semi-gradient Sarsa and Q-Learning algorithms were run for number runs to verify initial findings. While a total of 50 runs were run, with each being 500 episodes with a total max of 200 steps each episode, a sample of five runs and the cumulative reward are shown below.


Sarsa appears to unlearn the optimal policy, is prone to high variance. Sarsa has average cumulative reward roughly 23 with about 18 steps.The 2nd run of Sarsa results likely did not converge to the optimal value. Q-Learning on the other hand retains memory of the optimal policy, with the last run #5 having the most variance of the runs. Q-Learning learns a policy with an average cumulative reward of roughly 31 with about 10 steps. The true cumulative reward would be 42 with 8 steps. This matches the theory that Sarsa learns the near-optimal policy, while Q-Learning learns the optimal policy, but there is still room for algorithms to improve towards a more optimal policy.

![Episodic Q-Learning vs Sarsa Cumulative Reward Over Episodes](https://user-images.githubusercontent.com/13898053/47629273-66b95780-daf7-11e8-85e4-86059f0daefd.png)
![Table Averaging Steps and Cumulative Reward at the End of 500 Episodes For First 5 Runs](https://user-images.githubusercontent.com/13898053/47629298-881a4380-daf7-11e8-918f-969ef65cef76.png)

Using the same run samples, the policy weights were normalized, and then plotted as a heat map on the grid. Sarsa had a much harder time converging to the goal state at (4,4), which is reflected at (5,5) in the color maps below while Q-Learning correctly maps the goal state to be the most valuable position on the grid. The first two runs of Sarsa had an especially difficult time identifying the goal state, which makes sense in junction cumulative reward graphs as both these graphs show by the end of the run, the algorithm was unlearning the optimal policy. Additionally, Sarsa is more concerned about not traveling on the edges of the grid, which makes sense as the robot moves out of the grid, it’s punished with a reward of -10 while Q-Learning ignores the punishment. Sarsa encourages the agent to take the safer path to the goal position, which also explains why it takes Sarsa on average more steps to reach the goal state compared to Q-Learning.

![Learning Weights at the End of 500 Episodes For First 5 Runs](https://user-images.githubusercontent.com/13898053/47629461-6a011300-daf8-11e8-9d53-2382aee4b9b7.png)

## Takeaways / Further Work

This project really pushed the limits of my knowledge of machine learning and exposed me to many of the hot areas of research in reinforcement learning on mobile robots such as unlearning distal rewards, stuck in local optimas, handling multi-subgoals, poor sensor readings, difficulty in motion/path planning, finicky hyperparameters, and dealing with large state-spaces. 

In hindsight, it would've been better to use one of the popular ML libraries and done most of the computation on my laptop, and then made the robots do limited computation; if I tackle this problem again, this is likely the approach I would use. 

Additionally, both the algorithms I used, linear approximated SARSA and Q-Learning are not powerful enough for path-planning; [a non-linear approximation or converting the algorithms to their residual forms](http://www.cs.cmu.edu/afs/cs.cmu.edu/project/learn-43/lib/photoz/.g/web/glossary/linear.html) would likely be the next step. Another approach is to simply attempt an algorithm that doesn’t rely on bootstrapping so heavily, such as Monte Carlo methods would greatly increase the convergence as Monte Carlo value estimations are based on the true value of the state, and not on the approximated value of the state. I also suspect, while I'm not completely confident with deep learning, combining neural networks with RL would improve the learning and increase the state space.

Additionally, Arduino is too limited coding wise, which is why if you look through the commit history I removed nearly all the Arduino code.

## Built With
* [Arduino](https://www.arduino.cc/) - Initial Hardware Coding
* [Matlab](https://www.mathworks.com/products/matlab.html) - For plotting RL data


## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.


## Authors

* **Rebecca Dun** - [LinaeSostra](https://github.com/LinaeSostra)  


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* My code structure was heavily inspired by [Nick Walker's RL Arduino Work](https://github.com/nickswalker/ArduinoRL)
* [Willy Chung](https://www.linkedin.com/in/willyckh/) for his initial Arduino code of testing the motors and sensors on the phyiscal robots, and building both of these lovely robots from stratch single-handedly.
* My supervisor, [Dr. Rad](https://www.sfu.ca/mechatronics/people/faculty/ahmad_rad.html) that helped me see this project and elective through.
* Special thanks to Jacob Shimizu and [Michael Graves](https://github.com/Michael-Graves) that helped with rubber ducking through all the hurdles of this project.
