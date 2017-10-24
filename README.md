
### Usage:
Edit `MH.cpp` to change any compile-time parameters (everything except T (temperature) is a compile-time parameter).

Build:
```bash 
make
```

Run: 
```bash 
./MH-ising T tag
```

where T is the temperature, specified in units of the infinite-lattice critical temperature. i.e. `simulation_T = T*Tc = T*2./log(1 + sqrt(2.0))`
Note that this critical temperature is not the *actual* critical temperature since there is a correction factor (see Ferdinand and Fisher, 1969) due to the finite-size effects.

The string `tag` will be used to name the files produced.






