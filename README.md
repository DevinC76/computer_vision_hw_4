README FILE

<Devin Chen>

s1:The algorithm converts the image into a bianry image and find the centerx,centery,and radius of the sphere
    No Troubles here

s2:The algorithm calculates the direction and intensity of the light source. Filtering out to find the brighiest point. And returns the x,y,z component. This is by deriving the normal vector at the brightest point. n_bar = [x-x0,y-y0,z-z0] since Z is unknown z = sqrt(R^2 - (x-x0)^2 - (y-y0)^2)

    The trouble was finding sitting there realizing that I had to multiple by the brightest pixel value

s3: The algorithm creates a albedo image and a normal image. This is given by deriving the albedo and then finding the normal from the given direction and intensity of each image. 

    I still had some trouble at the end for some reason when I set the threshold very < 80 low it is core dumping. I think it has something to do with the albedo value being very close to 0

Here are my testing

./s1 ImagesForHW4/sphere0.pgm 80 s1.txt
./s2 s1.txt ImagesForHW4/sphere1.pgm ImagesForHW4/sphere2.pgm ImagesForHW4/sphere3.pgm s2.txt
./s3 s2.txt ImagesForHW4/sphere1.pgm ImagesForHW4/sphere2.pgm ImagesForHW4/sphere3.pgm 20 80 spherenormal.pgm spherealbedo.pgm

./s1 ImagesForHW4/object1.pgm 85 s1.txt
./s2 s1.txt ImagesForHW4/object1.pgm ImagesForHW4/object2.pgm ImagesForHW4/object3.pgm s2.txt
./s3 s2.txt ImagesForHW4/object1.pgm ImagesForHW4/object2.pgm ImagesForHW4/object3.pgm 20 85 spherenormal.pgm spherealbedo.pgm