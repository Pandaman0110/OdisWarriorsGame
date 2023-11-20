
local lume = require "lib/lume"
local cat_data = require "cat_data"

-----------------------------------

local cat = Cat.new()

cat.prefix = lume.randomchoice(cat_data.prefixes)
cat.suffix = lume.randomchoice(cat_data.suffixes)
cat.role = lume.randomchoice(cat_data.roles)

print(#cat_data.prefixes)



-----------------------------------


return cat