-- plugin

-- local fp = io.popen("env")
-- if fp then
--   print("Environment:")
--   print( fp:read("*all") )
--   fp:close()
-- else
--   print("could not popen'env'")
-- end

local nm = "/tmp/far-script1.lua"
local fp = assert( io.open(nm, "w") )
fp:write("print'Hello World'")
fp:close()
dofile(nm)
