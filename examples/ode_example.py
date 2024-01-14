"""
This is an example project demonstrating the functionality of the ODE methods
on the logistic growth model.
"""
import numpy as np
from numoop import ode
import numpy.typing as npt
import matplotlib.pyplot as plt

# Let's set up the model's parameters!
r = 0.1  # Growth rate
K = 100  # Carrying capacity
y0 = 10  # Initial population
h = 0.5  # Step
end = 50 # Final time

def logistic_growth(t, y):
    dydt = r * y * (1 - y / K)
    return dydt


# Let's perform the Euler's method!
res = ode.EulerScal(logistic_growth, y0, h, end)
sol = res.ode()

# Now let's plot the results!
t = (np.linspace(0,50,101)).reshape(-1, 1)
plt.scatter(t, sol)
plt.axhline(y=100, color='red', linestyle='--', label='Maximum capacity')
plt.xlabel('Time')
plt.ylabel('Population')
plt.title('Logistic growth')
plt.show()

# As we can see, as time goes forward, we approach
# the maximum capacity!