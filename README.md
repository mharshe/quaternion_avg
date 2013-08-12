quaternion_avg
==============

Get the average quaternion from a set of quaternions
-------------------

Since quaternions are not regular vectors, but rather representations of orientation, an average quaternion cannot just be obtained by taking a weighted mean. This function implements the work done by paper by F. Landis Merkley ([DOI: 10.2514/1.28949][paper]) to calculate the average quaternion.

(This code, along with its documentation, was originally hosted at http://msharshe.gemibox.net/knee-joint/html/).

###Dependencies

This C/C++ code needs the [GNU GSL][gsl] to be installed on the system.



[gsl]: http://www.gnu.org/software/gsl/
[paper]: http://dx.doi.org/10.2514/1.28949
