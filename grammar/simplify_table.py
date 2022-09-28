import pandas as pd
table = pd.read_html("table.html")[0]
table.index = table["Unnamed: 0"]
table.drop("Unnamed: 0", inplace=True, axis=1)
table.dropna(axis=0,how="all", inplace=True)

for i, (idx, info) in enumerate(table.iterrows()):
    if i == 0: continue
    print(i, idx)
    for col, cell in info.items():
        if not type(cell) is float:
            cell = cell.replace("Îµ", "#vazio#")
            print(col, " => ", cell)
    
    print("================================")