from PIL import Image

ter = Image.open("ter.ppm")
tre = Image.open("tre.ppm")

# Colors
deep_water = (0, 10, 100)
shallow_water = (40, 80, 140)
beach = (180, 180, 100)
grass = (100, 180, 100)
tree = (10, 100, 10)
stone = (160, 160, 160)
snow = (250, 250, 250)

out = Image.new("RGB", (1024, 1024))

M = 256**2 - 1

data = []

terd = list(ter.getdata())
tred = list(tre.getdata())

for i in range(0, len(terd)):
	if tred[i] > 65000:
		data.append(tree)
	else:
		if terd[i] < M*0.1:
			data.append(deep_water)
		elif terd[i] < M*0.15:
			data.append(shallow_water)
		elif terd[i] < M*0.2:
			data.append(beach)
		elif terd[i] < M*0.6:
			data.append(grass)
		elif terd[i] < M*0.8:
			data.append(stone)
		else:
			data.append(snow)

out.putdata(data)
out.save("final.png")
