import pandas as pd

# Example DataFrame (input)
data = {'user_id': [1, 2, 3], 'name': ['aLIce', 'bOB', 'CATHY']}
users = pd.DataFrame(data)

# Solution
def fix_names(users: pd.DataFrame) -> pd.DataFrame:
  # Capitalize the first letter and convert the rest to lowercase
  users['name'] = users['name'].str.capitalize()

  # Sort the DataFrame by user_id
  users = users.sort_values('user_id', ascending=True)

  return users

# Apply the function
fixed_users = fix_names(users)
print(fixed_users)
