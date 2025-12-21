import pandas as pd

def find_products(products: pd.DataFrame) -> pd.DataFrame:
    # Filter for products that are both low fat and recyclable
    # The & operator performs element-wise logical AND
    filtered_products = products[(products['low_fats'] == 'Y') & (products['recyclable'] == 'Y')]
    
    # Select only the 'product_id' column for the final output
    result = filtered_products[['product_id']]
    
    return result

# Example Usage:
data = {'product_id': [0, 1, 2, 3, 4], 
        'low_fats': ['Y', 'Y', 'N', 'Y', 'N'], 
        'recyclable': ['N', 'Y', 'Y', 'Y', 'N']}
products_df = pd.DataFrame(data)

output_df = find_products(products_df)
print(output_df)
