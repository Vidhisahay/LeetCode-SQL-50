import pandas as pd
import numpy as np

def calculate_special_bonus(employees: pd.DataFrame) -> pd.DataFrame:
    # Use np.where(condition, value_if_true, value_if_false)
    employees['bonus'] = np.where(
        (employees['employee_id'] % 2 == 1) & (~employees['name'].str.startswith('M')),
        employees['salary'], 
        0
    )
    
    # Select specific columns and sort by employee_id as required
    return employees[['employee_id', 'bonus']].sort_values('employee_id')
