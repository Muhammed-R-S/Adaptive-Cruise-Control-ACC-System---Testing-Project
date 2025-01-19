# Adaptive-Cruise-Control-ACC-System---Testing-Projec
This repository contains the testing framework for an Adaptive Cruise Control (ACC) System. The project ensures that the ACC system meets its functional requirements, with thorough unit testing and coverage analysis to validate its reliability and robustness.
--

The ACC System simulates an automotive feature designed to automatically adjust the vehicle's speed and maintain a safe distance from the vehicle ahead. This project focuses on testing the ACC system to ensure compliance with its functional requirements.
--
Scope of Contribution
--
My primary responsibility in this project was:

Designing, implementing, and executing test cases for the ACC system.
Ensuring comprehensive test coverage using tools like CUnit and gcov/lcov.
Analyzing test results to verify system behavior and identify any issues.
Features Tested
System Activation and Deactivation:

Activates only at valid speeds (30–150 km/h).
Deactivates upon brake press, low speed, or system errors.
Speed Adjustment:

Gradual increments or decrements to maintain cruising speed.
Distance Monitoring:

Reduces speed when too close to a vehicle ahead.
Increases speed when a safe distance is detected.
Error Handling:

Deactivation upon sensor or system errors.
Self-tests during activation.
