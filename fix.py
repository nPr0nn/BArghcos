
import cv2
import numpy as np

def hex_to_bgr(hex_color):
    """Convert a hex color code to BGR format."""
    hex_color = hex_color.lstrip('#')
    rgb = [int(hex_color[i:i+2], 16) for i in (0, 2, 4)]
    return (rgb[2], rgb[1], rgb[0])  # OpenCV uses BGR format


def replace_color_with_transparency(image_path, color_to_replace_hex, output_path):
    # Load the image
    image = cv2.imread(image_path)
    
    # Check if the image is already in RGBA format
    if image.shape[2] == 4:
        image = image[:, :, :3]  # Remove alpha channel if present

    # Convert hex color to BGR format
    color_to_replace = hex_to_bgr(color_to_replace_hex)
    
    # Create a mask for the color to replace
    mask = cv2.inRange(image, np.array(color_to_replace), np.array(color_to_replace))
    
    # Add an alpha channel to the image
    image_rgba = cv2.merge((image, np.ones((image.shape[0], image.shape[1]), dtype=np.uint8) * 255))
    
    # Set alpha channel to 0 where the mask is 255 (color to replace)
    image_rgba[:, :, 3][mask > 0] = 0
    
    # Save the output image
    cv2.imwrite(output_path, image_rgba)

def replace_color(image_path, color_to_replace_hex, replacement_color_hex, output_path):
    # Load the image
    image = cv2.imread(image_path)
    
    # Convert hex colors to BGR format
    color_to_replace = hex_to_bgr(color_to_replace_hex)
    replacement_color = hex_to_bgr(replacement_color_hex)
    
    # Create a mask for the color to replace
    mask = cv2.inRange(image, np.array(color_to_replace), np.array(color_to_replace))
    
    # Replace the color
    image[mask > 0] = replacement_color
    
    # Save the output image
    cv2.imwrite(output_path, image)

def replace_non_transparent_colors(image_path, replacement_color_hex, output_path):
    # Load the image with alpha channel (RGBA)
    image = cv2.imread(image_path, cv2.IMREAD_UNCHANGED)
    
    # Check if the image has 4 channels (RGBA)
    if image.shape[2] != 4:
        raise ValueError("Image does not have an alpha channel. Ensure the image is in RGBA format.")
    
    # Convert hex color to BGR format
    replacement_color = hex_to_bgr(replacement_color_hex)
    
    # Create a mask where alpha channel is not 0 (not transparent)
    mask = image[:, :, 3] > 0
    
    # Create an image filled with the replacement color
    replacement_image = np.zeros_like(image)
    replacement_image[:, :, :3] = replacement_color
    replacement_image[:, :, 3] = 255  # Fully opaque
    
    # Replace all non-transparent colors with the replacement color
    image[mask] = replacement_image[mask]
    
    # Save the output image
    cv2.imwrite(output_path, image)


def main():
    # replace_color('assets/maps/track.png', '#908058', '#0080f8', 'assets/maps/track2.png')
    # replace_color('assets/maps/track2.png', '#b0a070', '#58b0f8', 'assets/maps/track2.png')
    # replace_color_with_transparency('assets/maps/track2.png', '#000000', 'assets/maps/track2.png')
    replace_non_transparent_colors('assets/maps/track2.png', '#78d0f8', 'assets/maps/track2.png')

main()
