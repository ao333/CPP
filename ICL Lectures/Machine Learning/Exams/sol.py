from numpy import*
'''
Note:
1) KNN/Genetic/Beam/Best/CBR/IBL/Lazy/Eager/LWR were not covered due to pension strike, thus not examinable this year
2) Repeated questions will be skipped
3) Derivation/Diagram questions will be written on paper
Useful Links
http://galaxy.agh.edu.pl/~vlsi/AI/backp_t_en/backprop.html
http://www.cs.cmu.edu/afs/cs.cmu.edu/project/theo-5/www/mlcourse/ML95-handouts.html
http://cs231n.stanford.edu/syllabus.html
http://cs231n.github.io/neural-networks-case-study/
https://stats.stackexchange.com/questions/235528/backpropagation-with-softmax-cross-entropy
https://stats.stackexchange.com/questions/49528/batch-gradient-descent-versus-stochastic-gradient-descent
'''

# 2017 1a (Diagram on paper)
Ee = -3/7*log2(3/7) - 4/7*log2(4/7)
Esky = Ee - 4/7*(-3/4*log2(3/4)-1/4*log2(1/4)) - 0
Eair = Ee - 6/7*1 - 0
Ehum = Ee - 3/7*(-1/3*log2(1/3)-2/3*log2(2/3)) - 4/7*1
Ewin = Ee - 5/7*(-3/5*log2(3/5)-2/5*log2(2/5)) - 0
Ewat = Ee - 5/7*(-2/5*log2(2/5)-3/5*log2(3/5)) - 2/7*1
Efor = Ee - 4/7*1 - 3/7*(-2/3*log2(2/3)-1/3*log2(1/3))
# Choose Sky as it has the highest Information Gain > Sunny, as Rainy are all negative examples
Ee2 = -3/4*log2(3/4) - 1/4*log2(1/4)
# Eair2 Information Gain = 0, because Warm has identical remaining classification to Sunny
EHum2 = Ee2 - 2/4*0 - 2/4*1
Ewin2 = Ee2 - 3/4*0 - 0
# print(Ee, Esky, Eair, Ehum, Ewin, Ewat, Efor)
# print(Ee2, EHum2, Ewin2)
# Choose Wind as it has the highest Information Gain by having 2 perfect classifications
# Strong ends the tree with only positive examples while Weak ends its node having only 1 negative example

# 2017 2b
'''
To perfectly learn the target concept, the G and S boundaries must converge to be equivalent to it. At least 2 positive
examples are required to specify the max and min of the S target rectangle. For example, (2,6),(4,9) or (2,9),(4,6).
At least 4 negative examples are required to define the G, forming the four sides of the outer rectangle. For example,
(1,y1),(5,y2),(x1,7),(x2,10). Note that these boundaries are all one integer greater than the target concept, so as to
not cross/include any negative examples themselves. The least number of examples required to perfectly learn the target
concept is therefore 6. Note that if a,b,c,d are all bound between 0 and 10, then there is no need for examples to bound
G, therefore 2.
A query outside S but within G reduces the version space. A positive example generalises S, reducing VS, while a
negative one specializes G, also reducing VS. A query within S, or outside G will not reduce the VS, because its 
classification is already known. Therefore, we should keep feeding examples between S and G to reduce the gap
between the two rectangles, until we converge to one single target rectangle/concept.
'''
# 2017 3b
'''
L2 regularization works by multiplying half of the regularization rate by the squared sum of all weights. This differs
with L1 regularization which is simply the regularization rate times the sum of all weights. The square penalizes large
weights more aggressively since squared of numbers > 1 makes them extra large, vice versa. This means that L2
regularises large weights more than smaller weights. L1 on the other hand regularises all weights by a constant factor.
This can often lead to sparse or weight that are near 0. This is akin to removing the connections between the neurons.
'''
# 2017 3c
'''
There are multiple methods to improve generalization and thus prevent over-fitting. Some examples are:
1) Early Stopping: By monitoring both the training and test validation error (or classification rate), one can stop the
training early, after validation error stops reducing, even if training error keeps going down. If training continues,
the model will try to memorize the training set, leading to over fitting. stopping it early, improves generalisation.
2) Holdout Method: By dividing the data set into training, validation and testing sets, one can test the network using
data unseen by the training model. This prevents the training set from memorising specific features of the testing set,
therefore providing a better generalisation against future testing sets.
3) Regularisation: By penalizing large weights (using L2 for example), one can reduce the level to which a model relies
on any large, individual weights in determining an input classification. This is especially important if a large weight
learned a noisy feature. By reducing this weight, the model can generalise better using other weights/features.
4) Dropout (NN-specific): By randomly dropping neurons, a model can reduce its reliance on certain nodes, allowing
others to learn independent of their parents. This is especially important if a parent node learned a noisy feature.
Similar to L1 regularisation, this allows the model to generalise better without memorising certain features.
5) Model Topology: Number of layers, and neurons per layer
6) Random sequential search the hyper parameters for highest validation test score.
7) Optimize parameters using validation set
'''
# 2017 3d
# print("CR:", 1000/(1000+100+50+20+10+10+10))
'''
The classification rate given is certainly not suitable because Class 1 is significantly over-represented in the test
set. This distorts the classification rate since classifying class 1 correctly, will result in a high overall
classification rate regardless of how the model performs on other classes. Alternatives include:
1) Down-sampling: We can randomly down-sample the majority class according to the number of examples that the minority
example has. We can then repeat this procedure with different random samples, while monitoring the performance, mean
and standard deviation.   
2) Scaling: Divide each box by the total number of examples per its class. However, this does not solve the problem if
we cannot guarantee that there is same number of examples for each class.
3) Up-sampling: We can additionally introduce dummy examples, through data augmentation for example. This allows us to
balance out under-represented test sets. However, down-sampling is more desirable since up-sampling may incur
undesirable data distortions itself.
'''
# 2016 1s
Ep = -5/12*log2(5/12) - 7/12*log2(7/12)
Ehou = Ep - 5/12*(-3/5*log2(3/5)-2/5*log2(2/5)) - 4/12*1 - 0
Etra = Ep - 5/12*(-3/5*log2(3/5)-2/5*log2(2/5)) - 4/12*(-3/4*log2(3/4)-1/4*log2(1/4)) - 3/12*(-2/3*log2(2/3)-1/3*log2(1/3))
Edet = Ep - 7/12*(-5/7*log2(5/7)-2/7*log2(2/7)) - 5/12*(-3/5*log2(3/5)-2/5*log2(2/5))
Eduh = Ep - 5/12*(-4/5*log2(4/5)-1/5*log2(1/5)) - 7/12*(-4/7*log2(4/7)-3/7*log2(3/7))
# print(Ep, Ehou, Etra, Edet, Eduh)
# Choose House as it has the highest Information Gain > Acid and Electro as Deep no
# Acid Branch
EpA = -3/5*log2(3/5)-2/5*log2(2/5)
# Egoa2 no, Ebea2 no, EPhy yes
EdetA = EpA - 3/5*(-2/3*log2(2/3)-1/3*log2(1/3)) - 2/5*1
EduhA = EpA - 2/5*1 - 3/5*(-2/3*log2(2/3)-1/3*log2(1/3))
# print(EpA, EdetA, EduhA)
# Same information gain, Detroit and Dutch to be continued...
# Electro Branch
EpE = 1
EtraE = EpE - 1  # Beat and Psycho positive
# EdetE Yes yes, No no
EduhE = EpE - 3/5*(-2/3*log2(2/3)-1/3*log2(1/3)) - 0  # Moon no
#  Dutch to be continued...

# 2016 2a
'''
S0<0,0,0,0>
G0<?,?,?,?>
S1<acid,goa,no,moom>
G1<?,?,?,?>
S2<acid,goa,no,moom>
G2<acid,?,?,?> <?,goa,?,?> <?,?,no,?>
S3<acid,goa,no,?>
G3<acid,?,?,?> <?,goa,?,?> <?,?,no,?>
S4<acid,goa,no,?>
G4<acid,?,?,?> <?,goa,?,?>
S5<acid,goa,no,?>
G5<acid,?,?,?>
S6<acid,goa,?,?>
G6<acid,?,?,?>
S7<acid,goa,?,?>
G7<acid,?,?,?>
'''
# 2016 2b
'''
ID3 statistically uses all training examples at each step to refine its current hypothesis. This contrasts with C-E
which makes decisions incrementally per individual example. This makes ID3 much less sensitive to errors in individual
training examples. By stopping early, ID3 is able to imperfectly fit the training set, and thus better generalize on
unseen data. The reverse is true for C-E. In terms of search space, ID3 has a preference bias (for example shorter
trees), to break a tie, while C-E has a restriction bias. For example, a single noisy example may exclude C-E from
finding the target function all together, because it was excluded from C-E.
'''
# 2016 3b
'''
Quadratic loss outputs 0 or 1 then deltaW is 0 as well, so neurons die (gradient doesn't update). No matter if our
prediction is right or wrong deltaW will be 0 if the output is either 0 or 1. Binary Cross-entropy is a superior
error function scales like sigmoid, avoiding 0 gradient updates.
'''
# 2016 3c
'''
4) Dropout randomly removes nodes and weight links to those nodes. This allows the remaining nodes, to learn
independently of their parents or other dropped nodes. This is especially important if a parent node learned a noisy
feature. Popular retention probabilities are 0.5/0.8 for hidden neurons, and 0.8 to 1 (no dropping) for input.
'''
# 2016 3d (Refer to Refer to 2017 3d)
R1 = 400/(400+100)
R2 = 400/(400+100)  # Don't forget to compute recall2 and precision2!
P1 = 400/400
P2 = 400/400
F11 = 2*R1*P1/(R1+P1)
F12 = 2*R2*P2/(R2+P2)

# 2015 1a
'''
S0: X=<null,null>, Y=<null,null>
G0: X=<-inf,inf>, Y=<-inf,inf>
(5,3)+
S1= X=<5,5>, Y=<3,3>
G1: X=<-inf,inf>, Y=<-inf,inf>
(4,4)+
S1= X=<4,5>, Y=<3,4>
G1: X=<-inf,inf>, Y=<-inf,inf>
(6,5)+
S1= X=<4,6>, Y=<3,5>
G1: X=<-inf,inf>, Y=<-inf,inf>
(5,1)-
S1= X=<4,6>, Y=<3,5>
G1: X=<-inf,inf>, Y=<2,inf>
(5,8)-
S1= X=<4,6>, Y=<3,5>
G1: X=<-inf,inf>, Y=<2,7>
(9,4)-
S1= X=<4,6>, Y=<3,5>
G1: X=<-inf,8>, Y=<2,7>
(2,6)-
S1= X=<4,6>, Y=<3,5>
G1: X=<3,8>, Y=<2,7>
(1,3)-
S1= X=<4,6>, Y=<3,5>
G1: X=<3,8>, Y=<2,7>, X=<2,8>, Y=<2,5>
'''

# 2015 2c
'''
Regularisation works by penalizing large weights by scaling them by a constant or exponential factor. In the case of L1,
the new error function will have lambda * absolute sum of all weights, where lambda is the scaling factor. L2 penalizes
larger weights harder and smaller weights less by squaring wights. By penalizing large weights , one can reduce the
level to which a model relies on any large, individual weights in determining an input classification. This is
especially important if a large weight learned a noisy feature. By reducing this weight, the model can generalise better
using other weights/features.
'''
# 2015 2d
ErA = 1-0.8
Z = 2.58
n = 100
# print(ErA - Z*sqrt((ErA*(1-ErA))/n), ErA + Z*sqrt((ErA*(1-ErA))/n))
ErB = 1-0.77
n2 = 10000
# print(ErB - Z*sqrt((ErB*(1-ErB))/n2), ErB + Z*sqrt((ErB*(1-ErB))/n2))
'''
The confidence interval for class A means that with 99% confidence, the error will be between 0.097 and 0.303. Class B
has a much narrower distribution in that we can be 99% sure that the error lies between 0.219 and 0.241. While on the
surface it may seem obvious that class A with a higher classification rate will be better, Class B is actually tested
over more samples, thus giving us much more confidence of its performance. Nonetheless, it is NOT enough to use
distributions alone, because it doesn't tell us anything about the underlying inputs and algorithms. Thus, we will
need to use statistical tests (ex. T-tests to tell us if the mean performance is different. Statistically, Class A has
higher mean, but Class B has lower variance. Class A has smaller data set, overfit.
'''
# 2014 2a
ER = -3/5*log2(3/5)-2/5*log2(2/5)
Gtec = Ghou = Gven = ER - 4/5*(-3/4*log2(3/4)-1/4*log2(1/4)) - 0
Gdb = ER -2/5*1 - 3/5*(-2/3*log2(2/3)-1/3*log2(1/3))
# print(ER, Gtec, Gdb)
# DJ-AF and Price-20 are perfectly split, with entropy = 1, likely to be low information gain
# Choosing Techno since its first, even though House and D&B have equal information gain
# Tekkno no
ERtec = -3/4*log2(3/4)-1/4*log2(1/4)
Gven2 = ERtec - 3/4*0 - 1/4*0  # Venue perfectly classifies Deep, Egg no

# 2013 1a
'''
The solution is a 2-layer fully-connected Feed-forward Neural Network with 2 inputs, 1 hidden layer with 4 neurons and
1 output with 1 neuron. 2 inputs because the input data is 2 dimensional (X1,X2). 1 binary output neuron is adequate to 
classify 2 classes. One hidden layer is enough because there is a single compact region where the diamond and cross 
regions do not contain data from the other class. The region can be fully classified by a single output rectangle, thus 4
lines as boarders will suffice.
'''
# 2012 1a
'''
S0<0,0,0,0,0,0>
G0<?,?,?,?,?,?>
S1<sunny,warm,normal,strong,warm,same>
G1<?,?,?,?,?,?>
S2<sunny,warm,?,strong,warm,same>
G2<?,?,?,?,?,?>
S3<sunny,warm,?,strong,warm,same>
G3<sunny,?,?,?,?,?> <?,warm,?,?,?,?> <?,?,?,?,?,same>
S4<sunny,warm,?,strong,?,?>
G4<sunny,?,?,?,?,?> <?,warm,?,?,?,?>
S5<sunny,warm,?,strong,?,?>
G5<?,?,?,strong,?,?>
'''
# 2012 1b
Ees = -3/5*log2(3/5)-2/5*log2(2/5)
# Sky, Air, Wind all have similar information gain. Proceeding with Sky since it's first
IGsky = Ees -4/5*(-3/4*log2(3/4)-1/4*log2(1/4)) - 1/5*0  # Choosing Sunny since Rainy No
# wind has perfect classification
Eessky = -3/4*log2(3/4)-1/4*log2(1/4)
IGhum = Eessky - 3/4*0 - 1/4*0  # Strong Yes, Rainy No
# print(Ees, IGsky, Eessky, IGhum)

# 2011 1b
'''
The gradient descent algorithm intends to optimize a certain training function. The goal is usually to minimize a cost
function E by adjusting weight W. W is usually randomly initiated, and updated iteratively by deltaW. where deltaW = 
-LR*dE/dW (the gradient of the cost function with respect to the weights). LR is the learning rate which is used to 
scale the graidents in order to keep them low, and not jump over any local/global minimum or avoid oscillation.'''
# 2010 2a (Refer to 2013 1a for architecture)
'''
Perceptrons can only classify linear problems (using 1 line to divide data points into two regions). Thus, it is not
possible for perceptrons to separate/classify data using rectangle/ecliptic shapes, while multi-layer neurons will be
able to do so, given the number of activation functions involved.
'''
# 2010 2C (Refer to 2017 3b)
# 2010 3a (Too long, to be continued...)
# 2009 1a (Refer to 2012 1a for CE)
'''
F0<?,?,?,?,?,?>
F1<sunny,warm,normal,strong,warm,same>
F2<sunny,warm,?,strong,warm,same>
F3<sunny,warm,?,strong,?,?>
'''
# 2009 1b
'''
Find-S is identical to CE's S hypothesis. This is consistent with that fact that CE uses Find-S for its specific
hypothesis space.'''
# 2009 2b
'''
Sigmoid, ReLu, Step. ReLu is most commonly used in FFNN. Compared to Sigmoid and Step, the 45 degree slope of ReLu when
X>0, means that ReLu reduces the likelihood of a vanishing gradient, while Sigmoid's slope is almost flat when too far to
the right of X axis.
'''
# 2008 1a
Ea = 1
IG = Ea - 4/6*1-2/6*1
print(Ea, IG)
# 2008 1b
'''
Entropy is a measure of data impurity, meaning that the more evenly divided the data, the higher the entropy (to a max of
of 1). A scenario where all information is perfectly classified would result in an entropy of 0. Information gain is a
measure of the reduction in this impurity, meaning that if from the current vantage point, we want to move to a point
where entropy is low (meaning that we have higher information gain).
'''


# Mitchell Exercises
# 3.2
E32 = -3/6*log2(3/6) - 3/6*log2(3/6)
Ea2T = -2/4*log2(2/4) - 2/4*log2(2/4)
Ea2F = -1/2*log2(1/2) - 1/2*log2(1/2)
G32 = E32 - 4/6*Ea2T - 2/6*Ea2F
# print(E32, Ea2T, Ea2F, G32)

# 3.4
En = -3/5*log2(3/5) - 2/5*log2(2/5)
Gsky = En - 4/5*(-3/4*log2(3/4)-1/4*log2(1/4)) - 1/5*0
Gair = En - 4/5*(-3/4*log2(3/4)-1/4*log2(1/4)) - 1/5*0
Ghum = En - 2/5*(-1/2*log2(1/2)-1/2*log2(1/2)) - 3/5*(-2/3*log2(2/3)-1/3*log2(1/3))
# print(En, Gsky, Gair, Ghum)
# Choose Sky because its tied for highest Gain and Rain simplifies branching with an immediate No leaf
Esky2 = -3/4*log2(3/4) - 1/4*log2(1/4)
Gair2 = Esky2 - (-3/4*log2(3/4) - 1/4*log2(1/4))
Ghum2 = Esky2 -2/4*1 - 2/4*0
Gwin2 = Esky2 -3/4*0 - 1/4*0
# print(Esky, Gair2, Ghum2, Gwin2)
# Choose Sky(Sunny) > Wind(Strong)

# Evaluating Hypothesis
CR = (70+90)/(70+30+10+90)
Recall = 70/(70+30)
Recall2 = 90/(10+90)
Precision = 70/(70+10)
Precision2 = 90/(30+90)
F1 = 2*(Recall*Precision)/(Recall+Precision)
UAR = mean([Recall, Recall2])
F2 = 2*(Recall2*Precision2)/(Recall2+Precision2)
# print(CR, Recall, Precision, F1, UAR, F2)

# 4.3
'''
Equation (4.10) corresponds to incremental gradient descent in which weights 
are updated after seeing each of the examples, while Equation (4.7) corresponds 
to true gradient descent in which the weights are updated after seeing all the examples once.
'''