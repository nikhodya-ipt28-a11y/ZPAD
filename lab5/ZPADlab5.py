import streamlit as st
import pandas as pd
import plotly.express as px

# 1. Загрузка данных
@st.cache_data
def load_data():
    # Файл должен быть в той же папке!
    df = pd.read_csv('cleaned_vhi_data.csv')
    return df

try:
    df = load_data()
except FileNotFoundError:
    st.error("Файл 'cleaned_vhi_data.csv' не знайдено. Переконайся, що він у папці з кодом.")
    st.stop()

# --- ВЕРСТКА: КОЛОНКИ ---
# Левая колонка для фильтров, Правая для контента
col_sidebar, col_main = st.columns([1, 3])

with col_sidebar:
    st.header("Налаштування фільтрів")
    
    # Выбор индекса
    index_choice = st.selectbox("Оберіть часовий ряд:", ["VCI", "TCI", "VHI"])
    
    # Выбор области
    region_choice = st.selectbox("Оберіть область:", df['Province'].unique())
    
    # Слайдеры интервалов
    week_range = st.slider("Інтервал тижнів:", 1, 52, (1, 52))
    
    min_year = int(df['Year'].min())
    max_year = int(df['Year'].max())
    year_range = st.slider("Інтервал років:", min_year, max_year, (min_year, max_year))
    
    # Кнопка сброса
    if st.button("Скинути всі фільтри"):
        st.rerun()
    
    # Чекбоксы сортировки
    st.markdown("---")
    sort_asc = st.checkbox("Сортувати за зростанням")
    sort_desc = st.checkbox("Сортувати за спаданням")
    
    if sort_asc and sort_desc:
        st.warning("⚠️ Оберіть тільки один тип сортування!")

# --- ЛОГИКА ФИЛЬТРАЦИИ ---
filtered_df = df[
    (df['Province'] == region_choice) &
    (df['Year'].between(year_range[0], year_range[1])) &
    (df['Week'].between(week_range[0], week_range[1]))
]

# Сортировка (если выбран один чекбокс)
if sort_asc and not sort_desc:
    filtered_df = filtered_df.sort_values(by=index_choice, ascending=True)
elif sort_desc and not sort_asc:
    filtered_df = filtered_df.sort_values(by=index_choice, ascending=False)

# --- ВЕРСТКА: ПРАВАЯ ЧАСТЬ (ГРАФИКИ И ТАБЛИЦА) ---
with col_main:
    st.title("🛰 Аналіз стану рослинності (VHI)")
    
    tab1, tab2, tab3 = st.tabs(["📋 Таблиця", "📉 Графік часового ряду", "📊 Порівняння областей"])
    
    with tab1:
        st.subheader(f"Відфільтровані дані для: {region_choice}")
        st.dataframe(filtered_df, use_container_width=True)
    
    with tab2:
        st.subheader(f"Динаміка {index_choice} за обраний період")
        fig1 = px.line(filtered_df, x="Year", y=index_choice, color="Week", 
                      title=f"Зміна {index_choice} для {region_choice}")
        st.plotly_chart(fig1, use_container_width=True)
        
    with tab3:
        st.subheader("Порівняння області з іншими регіонами")
        # Данные для сравнения (все области в тот же период)
        comp_df = df[
            (df['Year'].between(year_range[0], year_range[1])) &
            (df['Week'].between(week_range[0], week_range[1]))
        ]
        fig2 = px.line(comp_df, x="Year", y=index_choice, color="Province",
                      title=f"Порівняння {index_choice} по областях")
        st.plotly_chart(fig2, use_container_width=True)