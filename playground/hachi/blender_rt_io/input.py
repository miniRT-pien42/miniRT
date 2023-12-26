import bpy
import math
import mathutils
import bmesh

bpy.context.scene.render.engine = 'CYCLES'

def parse_color(color_str):
    r, g, b = list(map(int, color_str.split(',')))
    return r / 255, g / 255, b / 255

def convert_coordinates(y_up_coordinates):
    # Y軸が上、Z軸が奥行きの座標からBlenderの座標系に変換
    x, y, z = y_up_coordinates
    return (x, z, y)  # YとZを交換

def parse_vector(vector_str):
    coordinates = list(map(float, vector_str.split(',')))
    return convert_coordinates(coordinates)  # 座標変換を適用

def align_object_to_normal(obj, normal):
    # Z軸（デフォルトのシリンダーの法線）と目標法線との間の回転行列を計算
    z_axis = mathutils.Vector((0, 0, 1))
    target_normal = mathutils.Vector(normal).normalized()
    rot_axis = z_axis.cross(target_normal)
    if rot_axis.length > 0:
        rot_axis.normalize()
        angle = z_axis.angle(target_normal)
        rot_matrix = mathutils.Matrix.Rotation(angle, 4, rot_axis)
    else:
        # 法線が同じ場合、回転は不要
        rot_matrix = mathutils.Matrix.Identity(4)

    obj.rotation_euler = rot_matrix.to_euler()

def look_at(obj, point):
    # カメラを特定の点に向ける
    obj_location = mathutils.Vector(obj.location)
    direction = mathutils.Vector(point) - obj_location
    # 回転を計算
    rot_quat = direction.to_track_quat('-Z', 'Y')
    obj.rotation_euler = rot_quat.to_euler()

def set_ambient_lighting(intensity, color):
    world = bpy.context.scene.world
    world.use_nodes = True
    nodes = world.node_tree.nodes
    bg = nodes.get("Background")
    if bg is None:
        bg = nodes.new(type="ShaderNodeBackground")

    # "World Output" ノードに接続
    world_output = nodes.get("World Output")
    if world_output is None:
        world_output = nodes.new(type="ShaderNodeOutputWorld")

    links = world.node_tree.links
    links.new(bg.outputs["Background"], world_output.inputs["Surface"])

    # 環境光の設定
    bg.inputs["Strength"].default_value = intensity * 0.1
    bg.inputs["Color"].default_value = (*color, 1.0)

def set_camera(location, direction, fov):
    cam_data = bpy.data.cameras.new("Camera")
    cam_obj = bpy.data.objects.new("Camera", cam_data)
    bpy.context.collection.objects.link(cam_obj)
    bpy.context.scene.camera = cam_obj
    cam_obj.location = location
    look_at(cam_obj, direction)
    cam_data.angle = math.radians(fov)

def set_light(location, intensity, color):
    light_data = bpy.data.lights.new(name="Light", type='POINT')
    light_obj = bpy.data.objects.new(name="Light", object_data=light_data)
    bpy.context.collection.objects.link(light_obj)
    light_obj.location = location
    light_data.energy = intensity * 30
    light_data.color = color

def create_sphere(location, diameter, color):
    bpy.ops.mesh.primitive_uv_sphere_add(radius=1, location=location)
    obj = bpy.context.object
    obj.data.materials.append(create_material(color))
    obj.scale = (diameter/2, diameter/2, diameter/2)

def create_plane(location, normal, color):
    bpy.ops.mesh.primitive_plane_add(size=1, location=location)
    obj = bpy.context.object
    align_object_to_normal(obj, normal)
    obj.data.materials.append(create_material(color))
    obj.scale = (1000, 1000, 1)

def create_cylinder(location, normal, diameter, height, color):
    bpy.ops.mesh.primitive_cylinder_add(radius=1, depth=height, location=location)
    obj = bpy.context.object
    obj.scale = (diameter/2, diameter/2, height/2)
    align_object_to_normal(obj, normal)
    bpy.context.view_layer.objects.active = obj
    bpy.ops.object.mode_set(mode='EDIT')
    mesh = bmesh.from_edit_mesh(obj.data)

    # 両端の面を選択
    for face in mesh.faces:
        if face.normal.z > 0.99 or face.normal.z < -0.99:  # Z軸に平行な面を検出
            face.select = True
        else:
            face.select = False

    # 選択された面を削除
    bmesh.update_edit_mesh(obj.data)
    bpy.ops.mesh.delete(type='FACE')
    bpy.ops.object.mode_set(mode='OBJECT')

    obj.data.materials.append(create_material(color))

def create_material(color):
    mat = bpy.data.materials.new(name="Material")
    mat.diffuse_color = (*color, 1.0)
    return mat

def parse_rt_file(filename):
    with open(filename, 'r') as file:
        for line in file:
            data = line.strip().split()
            identifier = data[0]
            if identifier == 'A':
                intensity = float(data[1])
                color = parse_color(data[2])
                set_ambient_lighting(intensity, color)
            if identifier == 'C':
                location = parse_vector(data[1])
                direction = parse_vector(data[2])
                fov = float(data[3])
                set_camera(location, direction, fov)
            elif identifier == 'L':
                location = parse_vector(data[1])
                intensity = float(data[2])
                color = parse_color(data[3])
                set_light(location, intensity, color)
            elif identifier == 'sp':
                location = parse_vector(data[1])
                diameter = float(data[2])
                color = parse_color(data[3])
                create_sphere(location, diameter, color)
            elif identifier == 'pl':
                location = parse_vector(data[1])
                normal = parse_vector(data[2])
                color = parse_color(data[3])
                create_plane(location, normal, color)
            elif identifier == 'cy':
                location = parse_vector(data[1])
                direction = parse_vector(data[2])
                diameter = float(data[3])
                height = float(data[4])
                color = parse_color(data[5])
                create_cylinder(location, direction, diameter, height, color)

# ファイルの読み込みと解析
parse_rt_file('/filepath/filename.rt')
