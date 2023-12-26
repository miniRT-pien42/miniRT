import bpy
import math

def transform_coordinate(coordinate):
    # 軸系の変換（YとZを入れ替え）
    return [round(coordinate[0], 2), round(coordinate[2], 2), round(coordinate[1], 2)]

def truncate_float(value, decimal_places=2):
    return float(f"{value:.{decimal_places}f}")

def write_rt_file(filepath):
    with open(filepath, 'w') as file:
        file.write(f"A  0.1            255,255,255\n")
        # シーン内の各オブジェクトに対して
        for obj in bpy.context.scene.objects:
            # カメラ
            if obj.type == 'CAMERA':
                loc = transform_coordinate(obj.location)
                cam_matrix = obj.rotation_euler.to_matrix()
                cam_direction = -cam_matrix.col[2].xyz  # カメラはマイナスZ軸を向いている
                cam_direction = [cam_direction.x, cam_direction.z, cam_direction.y]
                cam_direction = [round(d, 2) for d in cam_direction]
                fov = int(math.degrees(obj.data.angle))
                file.write(f"C {loc[0]},{loc[1]},{loc[2]} {cam_direction[0]},{cam_direction[1]},{cam_direction[2]} {fov}\n")

            # ライト
            elif obj.type == 'LIGHT':
                light_data = obj.data
                loc = transform_coordinate(obj.location)
                intensity = light_data.energy / 10
                color = [int(c * 255) for c in light_data.color]
                file.write(f"L {loc[0]},{loc[1]},{loc[2]} {intensity} {color[0]},{color[1]},{color[2]}\n")

            # メッシュ（プレーン、球、シリンダー）
            elif obj.type == 'MESH':
                loc = transform_coordinate(obj.location)
                color = [int(c * 255) for c in obj.active_material.diffuse_color[:3]]

                # オブジェクトの種類に応じて異なるフォーマットで書き出し
                if "Plane" in obj.name:
                    normal = obj.rotation_euler.to_matrix().to_4x4().col[2].xyz
                    normal = transform_coordinate(normal)
                    file.write(f"pl {loc[0]},{loc[1]},{loc[2]} {normal[0]},{normal[1]},{normal[2]} {color[0]},{color[1]},{color[2]}\n")

                elif "Sphere" in obj.name:
                    diameter = round(2 * obj.scale[0], 2)
                    file.write(f"sp {loc[0]},{loc[1]},{loc[2]} {diameter} {color[0]},{color[1]},{color[2]}\n")

                elif "Cylinder" in obj.name:
                    direction = obj.rotation_euler.to_matrix().to_4x4().col[2].xyz
                    direction = transform_coordinate(direction)
                    diameter = round(2 * obj.scale[0], 2)
                    height = round(2 * obj.scale[2], 2)
                    file.write(f"cy {loc[0]},{loc[1]},{loc[2]} {direction[0]},{direction[1]},{direction[2]} {diameter} {height} {color[0]},{color[1]},{color[2]}\n")

# RTファイルの書き出し
write_rt_file('/filepath/filename.rt')