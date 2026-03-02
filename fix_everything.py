import os, re

def write_file(path, content):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, 'w', encoding='utf-8') as f:
        f.write(content)

# 1. Настройка типов (как у Дарии Саввы в PR #327)
tasks_config = {
    'bruskova_v_image_smoothing': {'in': 'std::vector<int>', 'out': 'std::vector<int>'},
    'bruskova_v_char_frequency': {'in': 'std::string', 'out': 'int'},
    'bruskova_v_global_optimization': {'in': 'std::vector<double>', 'out': 'double'}
}

for ns, types in tasks_config.items():
    # Создаем common.hpp
    common_content = f'#pragma once\n#include <vector>\n#include <string>\n#include "task/include/task.hpp"\nnamespace {ns} {{\n  using InType = {types["in"]};\n  using OutType = {types["out"]};\n  using BaseTask = ppc::task::Task<InType, OutType>;\n}}'
    write_file(f'tasks/{ns}/common/include/common.hpp', common_content)

    # Правим .hpp файлы (SEQ и MPI)
    for mode in ['seq', 'mpi']:
        hpp_path = f'tasks/{ns}/{mode}/include/ops_{mode}.hpp'
        if os.path.exists(hpp_path):
            with open(hpp_path, 'r', encoding='utf-8') as f: content = f.read()
            content = re.sub(r'public ppc::task::Task<.*>', 'public BaseTask', content)
            if 'GetStaticTypeOfTask' not in content:
                type_flag = 'kSEQ' if mode == 'seq' else 'kMPI'
                content = re.sub(r'public:', f'public:\n  static constexpr ppc::task::TypeOfTask GetStaticTypeOfTask() {{ return ppc::task::TypeOfTask::{type_flag}; }}', content)
            write_file(hpp_path, content)

        # Правим .cpp файлы (Конструкторы)
        cpp_path = f'tasks/{ns}/{mode}/src/ops_{mode}.cpp'
        if os.path.exists(cpp_path):
            with open(cpp_path, 'r', encoding='utf-8') as f: content = f.read()
            class_name = f'BruskovaV{ns.split("_")[-1].capitalize()}{mode.upper()}'
            # Специальный фикс для имен классов Виолетты (ImageSmoothing, CharFrequency и т.д.)
            if 'image_smoothing' in ns: class_name = f'BruskovaVImageSmoothing{mode.upper()}'
            elif 'char_frequency' in ns: class_name = f'BruskovaVCharFrequency{mode.upper()}'
            elif 'global_optimization' in ns: class_name = f'BruskovaVGlobalOptimization{mode.upper()}'
            
            new_constructor = f'{class_name}::{class_name}(const InType &in) {{\n  SetTypeOfTask(GetStaticTypeOfTask());\n  GetInput() = in;\n}}'
            pattern = rf'{class_name}::{class_name}\(const InType &in\)\s*(?::\s*BaseTask\(\))?\s*\{{[^}}]*\}}'
            content = re.sub(pattern, new_constructor, content)
            write_file(cpp_path, content)

print("--- Все задачи Виолетты синхронизированы с эталоном! ---")