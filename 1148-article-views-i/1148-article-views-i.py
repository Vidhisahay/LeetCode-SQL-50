import pandas as pd

def article_views(views: pd.DataFrame) -> pd.DataFrame:
    # Filter for rows where the author_id is equal to the viewer_id
    self_views = views[views['author_id'] == views['viewer_id']]
    
    # Get unique author IDs, sort them, and rename the column to 'id'
    unique_authors = self_views['author_id'].drop_duplicates().sort_values().rename('id')
    
    # Convert the resulting Series to a DataFrame as required by the problem
    result_df = pd.DataFrame(unique_authors)
    
    return result_df

# Example Usage:
views_data = {
    'article_id': [1, 1, 2, 2, 4, 3, 3],
    'author_id': [3, 3, 7, 7, 7, 4, 4],
    'viewer_id': [5, 6, 7, 6, 1, 4, 4],
    'view_date': ['2019-08-01', '2019-08-02', '2019-08-01', '2019-08-02', '2019-07-22', '2019-07-21', '2019-07-21']
}
views_df = pd.DataFrame(views_data)
result = article_views(views_df)
print(result)
