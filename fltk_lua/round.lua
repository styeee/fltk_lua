os.execute("cls")

for y=1,32
do
	local line=""

	for x=1,32
	do
		local X=x-20
		local Y=y-20

		if (X*X+Y*Y)>125
		then
			line=line.."  "
		else
			line=line.."x "
		end
	end

	print(line)
end