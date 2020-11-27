st = "┌───────────┐"
p = [hex(ord(c)) for c in st]
rs = ""
for i in p:
    rs = rs + "\\u" + str(i)[2:]
print(rs.replace("\\ua","\\n"))
