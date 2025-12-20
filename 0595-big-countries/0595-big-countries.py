import pandas as pd
def big_countries (world: pd. DataFrame) -> pd.DataFrame:
    # Filter the rows based on the conditions for being a big country
    big_countries_df = world [(world['area'] >= 3000000) | (world ['population'] >= 25000000)]
   
    # Select the required columns
    result_df = big_countries_df[['name', 'population', 'area']]
    return result_df

# Sample data for the World table
data = {
    'name': ['Afghanistan', 'Albania', 'Algeria', 'Andorra', 'Angola'], 
    'continent': ['Asia', 'Europe', 'Africa', 'Europe', 'Africa'], 
    'area': [652230, 28748, 2381741, 468, 1246700], 'population': [25500100, 2831741, 37100000, 78115, 20609294],
    'gdp': [20343000000, 12960000000, 188681000000, 3712000000, 100990000000]
}

world_df = pd. DataFrame(data)

# Call the function with the sample data
result = big_countries (world_df)

print(result)