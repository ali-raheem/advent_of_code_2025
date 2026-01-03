# Day 8 WIP

It looks like the 1000 vectors are uniform over 0-100000 meaning that u32 would be needed to store each of the 3 coordinates.

u32 = 4 bytes, 3xu32 per vector = 12 bytes per vector.

= 12 KB of vector data alone without any storage of nearest neighbours.

My first idea was to shift the vectors to be centred over the origin but the uniform distribution poo-pooed that.

