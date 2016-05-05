Last project thing

Nathan Henry
Dan Porter
Stuart Bowman

Driver instructions:
	Run as-is to generate the images supplied

How to change stuff in the scene:

	The driver works by altering one of the three scene variables at a time. In order, the driver will create a scene using the full set of geometry from the geos vector, then loop through the camera positions, and within that, loop through the object translation/rotations. The name of each file indicates which configuration has been run.

	Filenames indicate the configuration that was run, with the first number indicating the starting shape, the second number indicating the camera position used, and the third indicating a boolean for if the shapes have been translated or moved in any way (0 = no movement, 1 = movement). For example, a filename of "sphere S0 C0 M0" indicates that the picture contains shape 0, camera position 0, TRS configuration 0 (no translation).

	Additionally, by changing the values in these three loops, you can direct the driver to only print certain configurations

	The geos vector dictates the geometry drawn in the scene. Change the objects added here to change the shapes that are drawn

	camPos vector lists the camera positions that will be sampled

	scale, rotY, geopos indicate the TRS values supplied to each individual shape

	objectColor vector indicates the colors of the supplied shapes

	upVector is the upVector for the camera

	lightPos is the worldspace position of the light

	