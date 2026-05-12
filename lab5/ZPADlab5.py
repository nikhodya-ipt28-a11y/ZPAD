import streamlit as st
import pandas as pd
import plotly.express as px
import os


@st.cache_data
def load_data(file_path):
    df = pd.read_csv(file_path)
    # Перетворення типів (про всяк випадок)
    df['Year'] = df['Year'].astype(int)
    df['Week'] = df['Week'].astype(int)
    return df


DATA_FILENAME = 'cleaned_vhi_data.csv'


if not os.path.exists(DATA_FILENAME):
    st.error(f"❌ Помилка: Файл '{DATA_FILENAME}' не знайдено!")
    st.info(f"""
    ### 🛠 Як виправити:
    1. Запустіть скрипт очищення даних з **Лабораторної роботи №2**.
    2. Отриманий файл `{DATA_FILENAME}` покладіть у папку з цим проєктом.
    3. Оновіть цю сторінку.
    """)
    st.stop()

df = load_data(DATA_FILENAME)


col_sidebar, col_main = st.columns([1, 3])

with col_sidebar:
    st.header("⚙️ Фільтри")
    
    index_choice = st.selectbox("Оберіть індекс:", ["VCI", "TCI", "VHI"])
    region_choice = st.selectbox("Оберіть область:", sorted(df['Province'].unique()))
    
    week_range = st.slider("Інтервал тижнів:", 1, 52, (1, 52))
    
    min_year, max_year = int(df['Year'].min()), int(df['Year'].max())
    year_range = st.slider("Інтервал років:", min_year, max_year, (min_year, max_year))
    
    if st.button("🔄 Скинути фільтри"):
        st.rerun()
    
    st.markdown("---")
    sort_asc = st.checkbox("🔼 Сортувати за зростанням")
    sort_desc = st.checkbox("🔽 Сортувати за спаданням")


filtered_df = df[
    (df['Province'] == region_choice) &
    (df['Year'].between(year_range[0], year_range[1])) &
    (df['Week'].between(week_range[0], week_range[1]))
].copy()

if sort_asc and not sort_desc:
    filtered_df = filtered_df.sort_values(by=index_choice, ascending=True)
elif sort_desc and not sort_asc:
    filtered_df = filtered_df.sort_values(by=index_choice, ascending=False)


with col_main:
    st.title("🛰 Аналіз стану рослинності (VHI)")
    
    tab1, tab2, tab3 = st.tabs(["📋 Таблиця", "📉 Динаміка", "📊 Порівняння"])
    
    with tab1:
        st.subheader(f"Дані для: {region_choice}")
        st.dataframe(filtered_df, use_container_width=True)
    
    with tab2:
        st.subheader(f"Зміна {index_choice} у часі")
        fig1 = px.line(filtered_df, x="Year", y=index_choice, color="Week", 
                      hover_data=["Week"], markers=True)
        st.plotly_chart(fig1, use_container_width=True)
        
    with tab3:
        st.subheader("Порівняння регіонів")
        comp_df = df[
            (df['Year'].between(year_range[0], year_range[1])) &
            (df['Week'].between(week_range[0], week_range[1]))
        ]
        fig2 = px.box(comp_df, x="Province", y=index_choice, color="Province",
                      title=f"Розподіл {index_choice} по областях")
        st.plotly_chart(fig2, use_container_width=True)
