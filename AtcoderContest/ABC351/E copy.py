def chebyshev_distance_sum(points):
    # Sort points based on x and y coordinates
    sorted_by_x = sorted(points, key=lambda p: p[0])
    sorted_by_y = sorted(points, key=lambda p: p[1])
    
    # Calculate contributions for each dimension
    def calculate_contributions(sorted_points):
        n = len(sorted_points)
        prefix_sum = 0
        contributions = [0] * n
        for i in range(n):
            x_i = sorted_points[i][0]
            contributions[i] = i * x_i - prefix_sum
            prefix_sum += x_i
        prefix_sum = 0
        for i in range(n - 1, -1, -1):
            x_i = sorted_points[i][0]
            contributions[i] += prefix_sum - (n - 1 - i) * x_i
            prefix_sum += x_i
        return contributions
    
    # Calculate total distance sum
    x_contributions = calculate_contributions(sorted_by_x)
    y_contributions = calculate_contributions(sorted_by_y)
    total_distance_sum = 0
    for x_contribution, y_contribution in zip(x_contributions, y_contributions):
        total_distance_sum += max(x_contribution, y_contribution)
    
    return total_distance_sum

# Example usage
points = [(1, 3), (4, 8), (6, 2), (5, 5), (9, 7)]
chebyshev_distance_sum(points)
