# Bounding Box Merger

# Paragraph:

You are given a list of rectangles in a 2D plane.
Each rectangle is defined by its bottom-left (x1, y1) and top-right (x2, y2) coordinates.

Some rectangles may overlap partially or completely.
You must implement a component that merges all overlapping rectangles into a minimal set of non-overlapping rectangles.

# Example:

Input:  
Rect1: (0, 0) → (10, 10)  
Rect2: (5, 5) → (15, 15)  
Rect3: (20, 20) → (30, 30)  

# Output:  
MergedRect1: (0, 0) → (15, 15)  
MergedRect2: (20, 20) → (30, 30)  

# Clarifications:

    You must model a Rectangle class (clean API).

    You must implement logic to merge overlapping rectangles.

    Rectangles that do not overlap must remain separate.

    The merged rectangles must cover the same area as the original set (no gaps, no overlaps).

    You must expose a clean API like mergeRectangles(vector<Rectangle>) → vector<Rectangle>.
